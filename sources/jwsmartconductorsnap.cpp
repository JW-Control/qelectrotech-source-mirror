/*
    JW Control extension for QElectroTech
    Smart conductor snapping keeps QET's native Terminal-Conductor-Terminal
    connectivity model while allowing a branch to be dropped onto an existing
    conductor. The new conductor shares one real terminal with the target
    conductor and follows the target path from the visual junction to that
    terminal, so the overlap is electrically explicit but visually invisible.
*/

#include "conductorautonumerotation.h"
#include "conductorprofile.h"
#include "conductorsegment.h"
#include "conductorsegmentprofile.h"
#include "diagram.h"
#include "qetgraphicsitem/conductor.h"
#include "qetgraphicsitem/terminal.h"
#include "undocommand/addgraphicsobjectcommand.h"

#include <QApplication>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QLineF>
#include <QMouseEvent>
#include <QPointer>
#include <QTimer>
#include <QUndoCommand>

#include <limits>

namespace {

constexpr int kSnapRadiusPixels = 14;
constexpr qreal kGeometryEpsilon = 0.25;

struct SnapCandidate
{
    QPointer<Conductor> conductor;
    QPointF scenePoint;
    int segmentIndex = -1;
    qreal distance = std::numeric_limits<qreal>::max();

    bool isValid() const
    {
        return conductor && segmentIndex >= 0;
    }
};

QGraphicsView *graphicsViewForObject(QObject *object)
{
    QWidget *widget = qobject_cast<QWidget *>(object);
    while (widget)
    {
        if (auto *view = qobject_cast<QGraphicsView *>(widget)) {
            return view;
        }
        widget = widget->parentWidget();
    }
    return nullptr;
}

QPoint mousePosition(const QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return event->position().toPoint();
#else
    return event->pos();
#endif
}

QPoint viewportPosition(QObject *watched,
                        QGraphicsView *view,
                        const QMouseEvent *event)
{
    QWidget *source_widget = qobject_cast<QWidget *>(watched);
    if (!source_widget || !view || !view->viewport()) {
        return mousePosition(event);
    }

    const QPoint local = mousePosition(event);
    if (source_widget == view->viewport()) {
        return local;
    }
    return view->viewport()->mapFrom(source_widget, local);
}

qreal sceneSnapRadius(QGraphicsView *view)
{
    if (!view) {
        return 12.0;
    }

    const QPointF p0 = view->mapToScene(QPoint(0, 0));
    const QPointF px = view->mapToScene(QPoint(kSnapRadiusPixels, 0));
    return qMax<qreal>(QLineF(p0, px).length(), 1.0);
}

Terminal *terminalAt(Diagram *diagram, const QPointF &scene_pos)
{
    if (!diagram) {
        return nullptr;
    }

    const QList<QGraphicsItem *> items = diagram->items(scene_pos);
    for (QGraphicsItem *item : items)
    {
        if (auto *terminal = qgraphicsitem_cast<Terminal *>(item)) {
            return terminal;
        }
    }
    return nullptr;
}

bool isBetweenInclusive(qreal value, qreal a, qreal b)
{
    const qreal minimum = qMin(a, b) - kGeometryEpsilon;
    const qreal maximum = qMax(a, b) + kGeometryEpsilon;
    return value >= minimum && value <= maximum;
}

SnapCandidate findSnapCandidate(Diagram *diagram,
                                Terminal *source,
                                const QPointF &mouse_scene_pos,
                                qreal radius)
{
    SnapCandidate best;
    if (!diagram || !source || diagram->isReadOnly()) {
        return best;
    }

    const QPointF source_dock = source->dockConductor();
    const Qet::Orientation source_orientation = source->orientation();
    const bool source_is_vertical =
            source_orientation == Qet::North || source_orientation == Qet::South;
    const bool source_is_horizontal =
            source_orientation == Qet::East || source_orientation == Qet::West;

    for (Conductor *conductor : diagram->conductors())
    {
        if (!conductor || conductor->terminal1 == source || conductor->terminal2 == source) {
            continue;
        }

        const QList<ConductorSegment *> segments = conductor->segmentsList();
        for (int index = 0; index < segments.size(); ++index)
        {
            ConductorSegment *segment = segments.at(index);
            if (!segment) {
                continue;
            }

            const QPointF p1 = conductor->mapToScene(segment->firstPoint());
            const QPointF p2 = conductor->mapToScene(segment->secondPoint());
            QPointF snap_point;
            bool compatible = false;

            // V1 deliberately favours a perpendicular branch. This preserves
            // the clean schematic style: a North/South terminal drops onto a
            // horizontal bus without adding a gratuitous elbow, and likewise
            // for East/West terminals onto vertical conductors.
            if (source_is_vertical && segment->isHorizontal()
                    && isBetweenInclusive(source_dock.x(), p1.x(), p2.x()))
            {
                snap_point = QPointF(source_dock.x(), p1.y());
                compatible = true;
            }
            else if (source_is_horizontal && segment->isVertical()
                     && isBetweenInclusive(source_dock.y(), p1.y(), p2.y()))
            {
                snap_point = QPointF(p1.x(), source_dock.y());
                compatible = true;
            }

            if (!compatible) {
                continue;
            }

            const qreal branch_length = QLineF(source_dock, snap_point).length();
            if (branch_length <= kGeometryEpsilon) {
                continue;
            }

            const qreal distance = QLineF(mouse_scene_pos, snap_point).length();
            if (distance <= radius && distance < best.distance)
            {
                best.conductor = conductor;
                best.scenePoint = snap_point;
                best.segmentIndex = index;
                best.distance = distance;
            }
        }
    }

    return best;
}

QList<QPointF> conductorScenePoints(Conductor *conductor)
{
    QList<QPointF> points;
    if (!conductor) {
        return points;
    }

    const QList<ConductorSegment *> segments = conductor->segmentsList();
    if (segments.isEmpty()) {
        return points;
    }

    points << conductor->mapToScene(segments.first()->firstPoint());
    for (ConductorSegment *segment : segments)
    {
        if (segment) {
            points << conductor->mapToScene(segment->secondPoint());
        }
    }
    return points;
}

qreal routeDistanceToFirst(const QList<QPointF> &points,
                           int segment_index,
                           const QPointF &snap_point)
{
    if (points.size() < 2 || segment_index < 0 || segment_index + 1 >= points.size()) {
        return std::numeric_limits<qreal>::max();
    }

    qreal distance = QLineF(snap_point, points.at(segment_index)).length();
    for (int index = segment_index - 1; index >= 0; --index) {
        distance += QLineF(points.at(index), points.at(index + 1)).length();
    }
    return distance;
}

qreal routeDistanceToLast(const QList<QPointF> &points,
                          int segment_index,
                          const QPointF &snap_point)
{
    if (points.size() < 2 || segment_index < 0 || segment_index + 1 >= points.size()) {
        return std::numeric_limits<qreal>::max();
    }

    qreal distance = QLineF(snap_point, points.at(segment_index + 1)).length();
    for (int index = segment_index + 1; index < points.size() - 1; ++index) {
        distance += QLineF(points.at(index), points.at(index + 1)).length();
    }
    return distance;
}

void appendUniquePoint(QList<QPointF> &points, const QPointF &point)
{
    if (points.isEmpty() || QLineF(points.last(), point).length() > kGeometryEpsilon) {
        points << point;
    }
}

bool buildBranchRoute(Terminal *source,
                      const SnapCandidate &snap,
                      Terminal **target_terminal,
                      QList<QPointF> *route)
{
    if (!source || !snap.isValid() || !target_terminal || !route) {
        return false;
    }

    Conductor *target_conductor = snap.conductor.data();
    const QList<QPointF> target_points = conductorScenePoints(target_conductor);
    if (target_points.size() < 2
            || snap.segmentIndex + 1 >= target_points.size())
    {
        return false;
    }

    Terminal *first_terminal = target_conductor->terminal1;
    Terminal *last_terminal = target_conductor->terminal2;
    const bool first_allowed = first_terminal && source->canBeLinkedTo(first_terminal);
    const bool last_allowed = last_terminal && source->canBeLinkedTo(last_terminal);
    if (!first_allowed && !last_allowed) {
        return false;
    }

    const qreal first_distance = first_allowed
            ? routeDistanceToFirst(target_points, snap.segmentIndex, snap.scenePoint)
            : std::numeric_limits<qreal>::max();
    const qreal last_distance = last_allowed
            ? routeDistanceToLast(target_points, snap.segmentIndex, snap.scenePoint)
            : std::numeric_limits<qreal>::max();

    const bool use_first = first_distance <= last_distance;
    *target_terminal = use_first ? first_terminal : last_terminal;

    route->clear();
    appendUniquePoint(*route, source->dockConductor());
    appendUniquePoint(*route, snap.scenePoint);

    if (use_first)
    {
        for (int index = snap.segmentIndex; index >= 0; --index) {
            appendUniquePoint(*route, target_points.at(index));
        }
    }
    else
    {
        for (int index = snap.segmentIndex + 1; index < target_points.size(); ++index) {
            appendUniquePoint(*route, target_points.at(index));
        }
    }

    return route->size() >= 3;
}

bool applyRouteProfile(Conductor *conductor, const QList<QPointF> &route)
{
    if (!conductor || route.size() < 3) {
        return false;
    }

    ConductorProfile profile;
    profile.beginOrientation = conductor->terminal1->orientation();
    profile.endOrientation = conductor->terminal2->orientation();

    for (int index = 0; index < route.size() - 1; ++index)
    {
        const QPointF delta = route.at(index + 1) - route.at(index);
        const bool horizontal = qAbs(delta.y()) <= kGeometryEpsilon;
        const bool vertical = qAbs(delta.x()) <= kGeometryEpsilon;

        if (!horizontal && !vertical) {
            profile.setNull();
            return false;
        }

        const qreal length = horizontal ? delta.x() : delta.y();
        if (qAbs(length) <= kGeometryEpsilon) {
            continue;
        }

        profile.segments << new ConductorSegmentProfile(length, horizontal);
    }

    if (profile.segments.size() < 2) {
        profile.setNull();
        return false;
    }

    conductor->setProfile(profile, Qt::TopLeftCorner);
    conductor->setProfile(profile, Qt::TopRightCorner);
    conductor->setProfile(profile, Qt::BottomLeftCorner);
    conductor->setProfile(profile, Qt::BottomRightCorner);
    return true;
}

bool addSmartBranch(Diagram *diagram,
                    Terminal *source,
                    const SnapCandidate &snap)
{
    if (!diagram || !source || !snap.isValid()
            || diagram->isReadOnly() || source->diagram() != diagram)
    {
        return false;
    }

    Terminal *target_terminal = nullptr;
    QList<QPointF> route;
    if (!buildBranchRoute(source, snap, &target_terminal, &route)
            || !target_terminal || target_terminal->diagram() != diagram)
    {
        return false;
    }

    auto *new_conductor = new Conductor(source, target_terminal);
    if (!new_conductor->isValid())
    {
        delete new_conductor;
        return false;
    }

    if (!applyRouteProfile(new_conductor, route))
    {
        delete new_conductor;
        return false;
    }

    // Keep the native QET potential-property behaviour. Because the branch
    // shares a real endpoint with the target conductor, relatedPotentialConductors()
    // immediately sees the existing potential.
    QSet<Conductor *> potential_conductors =
            new_conductor->relatedPotentialConductors();

    ConductorProperties inherited_properties;
    bool use_properties = !potential_conductors.isEmpty();
    if (use_properties)
    {
        inherited_properties = (*potential_conductors.begin())->properties();
        for (Conductor *conductor : potential_conductors)
        {
            if (conductor->properties() != inherited_properties)
            {
                use_properties = false;
                break;
            }
        }
    }

    auto *undo = new QUndoCommand(
            QObject::tr("Conectar conductor a potencial existente"));
    new AddGraphicsObjectCommand(new_conductor, diagram, QPointF(), undo);

    if (use_properties)
    {
        Conductor *other = potential_conductors.values().first();
        new_conductor->rSequenceNum() = other->sequenceNum();
        new_conductor->setProperties(inherited_properties);
    }
    else
    {
        ConductorAutoNumerotation numbering(new_conductor, diagram, undo);
        numbering.numerate();
    }

    diagram->undoStack().push(undo);

    if (use_properties)
    {
        Conductor *other = potential_conductors.values().first();
        new_conductor->setProperties(other->properties());
    }

    return true;
}

class JwSmartConductorSnapFilter final : public QObject
{
    public:
        explicit JwSmartConductorSnapFilter(QObject *parent = nullptr) :
            QObject(parent)
        {
        }

    protected:
        bool eventFilter(QObject *watched, QEvent *event) override
        {
            if (!event) {
                return false;
            }

            if (event->type() != QEvent::MouseButtonPress
                    && event->type() != QEvent::MouseMove
                    && event->type() != QEvent::MouseButtonRelease)
            {
                return false;
            }

            auto *mouse_event = static_cast<QMouseEvent *>(event);
            QGraphicsView *view = graphicsViewForObject(watched);
            if (!view || !view->viewport()) {
                return false;
            }

            auto *diagram = qobject_cast<Diagram *>(view->scene());
            if (!diagram) {
                return false;
            }

            const QPoint viewport_pos =
                    viewportPosition(watched, view, mouse_event);
            const QPointF scene_pos = view->mapToScene(viewport_pos);

            if (event->type() == QEvent::MouseButtonPress)
            {
                if (mouse_event->button() != Qt::LeftButton || diagram->isReadOnly()) {
                    return false;
                }

                resetDrag();
                m_source = terminalAt(diagram, scene_pos);
                m_diagram = m_source ? diagram : nullptr;
                m_view = m_source ? view : nullptr;
                return false;
            }

            if (!m_source || !m_diagram || diagram != m_diagram) {
                return false;
            }

            if (event->type() == QEvent::MouseMove)
            {
                if (!(mouse_event->buttons() & Qt::LeftButton)) {
                    resetDrag();
                    return false;
                }

                // A real terminal always has priority. Native QET keeps its
                // existing terminal-to-terminal hover colours and rules.
                Terminal *hover_terminal = terminalAt(diagram, scene_pos);
                if (hover_terminal && hover_terminal != m_source)
                {
                    clearSnapHighlight();
                    return false;
                }

                const SnapCandidate candidate = findSnapCandidate(
                        diagram,
                        m_source,
                        scene_pos,
                        sceneSnapRadius(view));

                if (!candidate.isValid())
                {
                    clearSnapHighlight();
                    return false;
                }

                setSnapHighlight(candidate);

                // Application event filters run before QGraphicsView dispatches
                // the move to Terminal. Let QET process the event normally so
                // its mouse-grabber state stays untouched, then snap the dashed
                // preview endpoint at the end of this event-loop turn.
                const QPointer<Diagram> diagram_guard = diagram;
                const QPointF snap_point = candidate.scenePoint;
                QTimer::singleShot(0, [diagram_guard, snap_point]() {
                    if (diagram_guard) {
                        diagram_guard->setConductorStop(snap_point);
                    }
                });
                return false;
            }

            if (event->type() == QEvent::MouseButtonRelease)
            {
                if (mouse_event->button() != Qt::LeftButton) {
                    return false;
                }

                // A terminal under the cursor remains a native QET connection.
                Terminal *release_terminal = terminalAt(diagram, scene_pos);
                if (release_terminal && release_terminal != m_source)
                {
                    resetDrag();
                    return false;
                }

                const SnapCandidate candidate = findSnapCandidate(
                        diagram,
                        m_source,
                        scene_pos,
                        sceneSnapRadius(view));

                if (!candidate.isValid())
                {
                    resetDrag();
                    return false;
                }

                // Do not swallow the release: QGraphicsScene must receive it
                // to finish its native mouse grab cleanly. Native Terminal will
                // stop the preview and ignore the conductor body; immediately
                // afterwards we create the smart branch in a queued callback.
                const QPointer<Diagram> diagram_guard = diagram;
                const QPointer<Terminal> source_guard = m_source;
                const SnapCandidate queued_candidate = candidate;
                resetDrag();

                QTimer::singleShot(0, [diagram_guard, source_guard, queued_candidate]() {
                    if (diagram_guard && source_guard && queued_candidate.isValid()) {
                        addSmartBranch(diagram_guard, source_guard, queued_candidate);
                    }
                });
                return false;
            }

            return false;
        }

    private:
        void clearSnapHighlight()
        {
            if (m_highlighted_conductor) {
                m_highlighted_conductor->setHighlighted(m_previous_highlight);
            }
            m_highlighted_conductor = nullptr;
            m_previous_highlight = Conductor::None;
        }

        void setSnapHighlight(const SnapCandidate &candidate)
        {
            if (m_highlighted_conductor == candidate.conductor) {
                return;
            }

            clearSnapHighlight();
            m_highlighted_conductor = candidate.conductor;
            if (m_highlighted_conductor)
            {
                m_previous_highlight = m_highlighted_conductor->highlight();
                m_highlighted_conductor->setHighlighted(Conductor::Normal);
            }
        }

        void resetDrag()
        {
            clearSnapHighlight();
            m_source = nullptr;
            m_diagram = nullptr;
            m_view = nullptr;
        }

    private:
        QPointer<Terminal> m_source;
        QPointer<Diagram> m_diagram;
        QPointer<QGraphicsView> m_view;
        QPointer<Conductor> m_highlighted_conductor;
        Conductor::Highlight m_previous_highlight = Conductor::None;
};

JwSmartConductorSnapFilter *s_smart_conductor_snap_filter = nullptr;

void installJwSmartConductorSnap()
{
    if (!qApp || s_smart_conductor_snap_filter) {
        return;
    }

    s_smart_conductor_snap_filter = new JwSmartConductorSnapFilter(qApp);
    qApp->installEventFilter(s_smart_conductor_snap_filter);
}

} // namespace

Q_COREAPP_STARTUP_FUNCTION(installJwSmartConductorSnap)
