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
#include <QKeyEvent>
#include <QLineF>
#include <QMouseEvent>
#include <QPointer>
#include <QTimer>
#include <QUndoCommand>
#include <QVector>

#include <limits>

namespace {

constexpr int kSnapRadiusPixels = 14;
constexpr qreal kReleaseHysteresisFactor = 1.35;
constexpr int kPointerWatchdogMs = 60;
constexpr qreal kGeometryEpsilon = 0.25;

struct SnapCandidate
{
    QPointer<Conductor> conductor;
    QPointF scenePoint;
    int segmentIndex = -1;
    bool segmentHorizontal = false;
    qreal distance = std::numeric_limits<qreal>::max();

    bool isValid() const
    {
        return conductor && segmentIndex >= 0;
    }
};

struct SnapSegment
{
    QPointer<Conductor> conductor;
    QPointF first;
    QPointF second;
    int segmentIndex = -1;
    bool horizontal = false;
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

QPoint globalMousePosition(const QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return event->globalPosition().toPoint();
#else
    return event->globalPos();
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

QPointF scenePositionForEvent(QObject *watched,
                              QGraphicsView *view,
                              const QMouseEvent *event)
{
    if (!view || !view->viewport()) {
        return QPointF();
    }

    QGraphicsView *event_view = graphicsViewForObject(watched);
    if (event_view == view) {
        return view->mapToScene(viewportPosition(watched, view, event));
    }

    // A release can happen over another widget (or after the pointer leaves
    // the viewport). Map its global position back into the original view so
    // the drag can always be terminated cleanly.
    const QPoint viewport_pos =
            view->viewport()->mapFromGlobal(globalMousePosition(event));
    return view->mapToScene(viewport_pos);
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

qreal clampValue(qreal value, qreal a, qreal b)
{
    const qreal minimum = qMin(a, b);
    const qreal maximum = qMax(a, b);
    return qMax(minimum, qMin(maximum, value));
}

QPointF closestPointOnSegment(const QPointF &mouse_scene_pos,
                              const QPointF &p1,
                              const QPointF &p2,
                              bool horizontal)
{
    // Keep the junction on QET's grid along the conductor whenever possible.
    // The conductor's fixed coordinate is preserved exactly, so the point can
    // never drift away from the visible wire.
    const QPointF grid_point = Diagram::snapToGrid(mouse_scene_pos);

    if (horizontal)
    {
        return QPointF(
                clampValue(grid_point.x(), p1.x(), p2.x()),
                p1.y());
    }

    return QPointF(
            p1.x(),
            clampValue(grid_point.y(), p1.y(), p2.y()));
}

qreal distanceToOrthogonalSegment(const QPointF &mouse_scene_pos,
                                  const QPointF &p1,
                                  const QPointF &p2,
                                  bool horizontal)
{
    QPointF raw_projection;
    if (horizontal)
    {
        raw_projection = QPointF(
                clampValue(mouse_scene_pos.x(), p1.x(), p2.x()),
                p1.y());
    }
    else
    {
        raw_projection = QPointF(
                p1.x(),
                clampValue(mouse_scene_pos.y(), p1.y(), p2.y()));
    }
    return QLineF(mouse_scene_pos, raw_projection).length();
}

QVector<SnapSegment> buildSnapSegments(Diagram *diagram, Terminal *source)
{
    QVector<SnapSegment> cached_segments;
    if (!diagram || !source || diagram->isReadOnly()) {
        return cached_segments;
    }

    for (Conductor *conductor : diagram->conductors())
    {
        if (!conductor
                || conductor->terminal1 == source
                || conductor->terminal2 == source)
        {
            continue;
        }

        const QList<ConductorSegment *> segments = conductor->segmentsList();
        for (int index = 0; index < segments.size(); ++index)
        {
            ConductorSegment *segment = segments.at(index);
            if (!segment || segment->isPoint()) {
                continue;
            }

            const bool horizontal = segment->isHorizontal();
            const bool vertical = segment->isVertical();
            if (!horizontal && !vertical) {
                continue;
            }

            SnapSegment cached;
            cached.conductor = conductor;
            cached.first = conductor->mapToScene(segment->firstPoint());
            cached.second = conductor->mapToScene(segment->secondPoint());
            cached.segmentIndex = index;
            cached.horizontal = horizontal;
            cached_segments.append(cached);
        }
    }

    return cached_segments;
}

SnapCandidate findSnapCandidate(Terminal *source,
                                const QPointF &mouse_scene_pos,
                                qreal radius,
                                const QVector<SnapSegment> &cached_segments)
{
    SnapCandidate best;
    if (!source) {
        return best;
    }

    const QPointF source_dock = source->dockConductor();

    // Geometry is cached once when the drag starts. QET deliberately runs its
    // QGraphicsScene without a spatial index, so rebuilding every conductor's
    // segment list on every mouse move was noticeably expensive on real pages.
    for (const SnapSegment &segment : cached_segments)
    {
        Conductor *conductor = segment.conductor.data();
        if (!conductor) {
            continue;
        }

        const qreal distance = distanceToOrthogonalSegment(
                mouse_scene_pos,
                segment.first,
                segment.second,
                segment.horizontal);

        if (distance > radius || distance >= best.distance) {
            continue;
        }

        const QPointF snap_point = closestPointOnSegment(
                mouse_scene_pos,
                segment.first,
                segment.second,
                segment.horizontal);
        if (QLineF(source_dock, snap_point).length() <= kGeometryEpsilon) {
            continue;
        }

        best.conductor = conductor;
        best.scenePoint = snap_point;
        best.segmentIndex = segment.segmentIndex;
        best.segmentHorizontal = segment.horizontal;
        best.distance = distance;
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

bool terminalAxisIsVertical(Terminal *source)
{
    if (!source) {
        return true;
    }
    const Qet::Orientation orientation = source->orientation();
    return orientation == Qet::North || orientation == Qet::South;
}

void appendOrthogonalApproach(QList<QPointF> &route,
                              Terminal *source,
                              const SnapCandidate &snap)
{
    const QPointF start = source->dockConductor();
    const QPointF end = snap.scenePoint;
    appendUniquePoint(route, start);

    const qreal dx = end.x() - start.x();
    const qreal dy = end.y() - start.y();
    if (qAbs(dx) <= kGeometryEpsilon || qAbs(dy) <= kGeometryEpsilon)
    {
        appendUniquePoint(route, end);
        return;
    }

    const bool start_vertical = terminalAxisIsVertical(source);
    // To create a clean T, the last visible branch segment should be
    // perpendicular to the target conductor.
    const bool final_vertical = snap.segmentHorizontal;

    if (start_vertical != final_vertical)
    {
        // One elbow is enough while preserving both the source axis and a
        // perpendicular arrival at the target conductor.
        const QPointF elbow = start_vertical
                ? QPointF(start.x(), end.y())
                : QPointF(end.x(), start.y());
        appendUniquePoint(route, elbow);
        appendUniquePoint(route, end);
        return;
    }

    // Start and final segments need the same axis. Use a centered dog-leg so
    // diagonal mouse intent becomes an orthogonal, schematic-friendly route.
    if (start_vertical)
    {
        qreal middle_y = start.y() + dy / 2.0;
        middle_y = Diagram::snapToGrid(QPointF(start.x(), middle_y)).y();
        if (qAbs(middle_y - start.y()) <= kGeometryEpsilon
                || qAbs(middle_y - end.y()) <= kGeometryEpsilon)
        {
            middle_y = start.y() + dy / 2.0;
        }
        appendUniquePoint(route, QPointF(start.x(), middle_y));
        appendUniquePoint(route, QPointF(end.x(), middle_y));
    }
    else
    {
        qreal middle_x = start.x() + dx / 2.0;
        middle_x = Diagram::snapToGrid(QPointF(middle_x, start.y())).x();
        if (qAbs(middle_x - start.x()) <= kGeometryEpsilon
                || qAbs(middle_x - end.x()) <= kGeometryEpsilon)
        {
            middle_x = start.x() + dx / 2.0;
        }
        appendUniquePoint(route, QPointF(middle_x, start.y()));
        appendUniquePoint(route, QPointF(middle_x, end.y()));
    }

    appendUniquePoint(route, end);
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
    appendOrthogonalApproach(*route, source, snap);

    // From the visual junction onward, reuse the target conductor's exact
    // route. That overlap is invisible but keeps QET's native connectivity to
    // a real terminal and therefore preserves potential tracking.
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
    if (!conductor || route.size() < 2) {
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

    if (profile.segments.isEmpty()) {
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
    // shares a real endpoint with the target conductor,
    // relatedPotentialConductors() immediately sees the existing potential.
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
            m_pointer_watchdog.setInterval(kPointerWatchdogMs);
            connect(&m_pointer_watchdog, &QTimer::timeout, this, [this]() {
                if (QApplication::mouseButtons() & Qt::LeftButton) {
                    return;
                }

                // Windows can steal the release while taking a screenshot or
                // switching applications. If QET never receives that release,
                // kill the preview here instead of leaving a dashed wire hanging.
                cancelTrackedPreview();
            });
        }

    protected:
        bool eventFilter(QObject *watched, QEvent *event) override
        {
            if (!event) {
                return false;
            }

            // Cancel paths must work even when the pointer has already left
            // the QGraphicsView. ApplicationStateChange covers Windows shell
            // overlays (notably Win+Shift+S) that do not always deliver the
            // same deactivate sequence as a normal Alt+Tab.
            if (event->type() == QEvent::ApplicationDeactivate
                    || event->type() == QEvent::WindowDeactivate
                    || (event->type() == QEvent::ApplicationStateChange
                        && QApplication::applicationState() != Qt::ApplicationActive))
            {
                if (m_source || m_recent_diagram) {
                    cancelTrackedPreview();
                }
                return false;
            }

            if (m_source && event->type() == QEvent::KeyPress)
            {
                auto *key_event = static_cast<QKeyEvent *>(event);
                if (key_event->key() == Qt::Key_Escape)
                {
                    cancelTrackedPreview();
                    return false;
                }
            }

            if (m_source && event->type() == QEvent::UngrabMouse)
            {
                cancelTrackedPreview();
                return false;
            }

            if (event->type() != QEvent::MouseButtonPress
                    && event->type() != QEvent::MouseMove
                    && event->type() != QEvent::MouseButtonRelease)
            {
                return false;
            }

            auto *mouse_event = static_cast<QMouseEvent *>(event);

            if (event->type() == QEvent::MouseButtonPress)
            {
                if (m_source && mouse_event->button() != Qt::LeftButton)
                {
                    cancelTrackedPreview();
                    return false;
                }

                if (mouse_event->button() != Qt::LeftButton) {
                    return false;
                }

                QGraphicsView *view = graphicsViewForObject(watched);
                if (!view || !view->viewport()) {
                    return false;
                }

                auto *diagram = qobject_cast<Diagram *>(view->scene());
                if (!diagram || diagram->isReadOnly()) {
                    return false;
                }

                cancelTrackedPreview();
                m_recent_diagram = diagram;
                m_pointer_watchdog.start();

                const QPointF scene_pos = scenePositionForEvent(
                        watched, view, mouse_event);

                Terminal *source = terminalAt(diagram, scene_pos);
                if (source) {
                    beginDrag(source, diagram, view);
                }

                // Our viewport hit-test runs before QGraphicsScene dispatches
                // the press. If a theme/zoom edge case misses the terminal,
                // ask QET which item actually became the native mouse grabber
                // once the press has finished processing.
                const QPointer<Diagram> diagram_guard = diagram;
                const QPointer<QGraphicsView> view_guard = view;
                QTimer::singleShot(0, this, [this, diagram_guard, view_guard]() {
                    if (!diagram_guard || !view_guard || m_source) {
                        return;
                    }

                    auto *native_source = qgraphicsitem_cast<Terminal *>(
                            diagram_guard->mouseGrabberItem());
                    if (native_source
                            && native_source->diagram() == diagram_guard)
                    {
                        beginDrag(
                                native_source,
                                diagram_guard.data(),
                                view_guard.data());
                    }
                });
                return false;
            }

            // Even if our source-terminal detection failed, a left-button
            // release must never leave QET's native conductor setter visible.
            if (event->type() == QEvent::MouseButtonRelease
                    && mouse_event->button() == Qt::LeftButton
                    && !m_source)
            {
                if (m_recent_diagram) {
                    m_recent_diagram->setConductor(false);
                }
                m_pointer_watchdog.stop();
                return false;
            }

            if (!m_source || !m_diagram || !m_view) {
                return false;
            }

            Diagram *diagram = m_diagram.data();
            QGraphicsView *view = m_view.data();
            if (!diagram || !view) {
                resetDrag();
                return false;
            }

            const QPointF scene_pos = scenePositionForEvent(
                    watched, view, mouse_event);

            if (event->type() == QEvent::MouseMove)
            {
                if (!(mouse_event->buttons() & Qt::LeftButton))
                {
                    cancelTrackedPreview();
                    return false;
                }

                const SnapCandidate candidate = findSnapCandidate(
                        m_source,
                        scene_pos,
                        m_snap_radius,
                        m_snap_segments);

                if (!candidate.isValid())
                {
                    clearSnapHighlight();
                    return false;
                }

                // Only pay for the scene hit-test when we are actually near a
                // snap target. Native QET already does its own item lookup on
                // every move, so avoiding our duplicate lookup in open space
                // noticeably reduces pointer drag cost.
                Terminal *hover_terminal = terminalAt(diagram, scene_pos);
                if (hover_terminal && hover_terminal != m_source)
                {
                    clearSnapHighlight();
                    return false;
                }

                setSnapHighlight(candidate);
                scheduleSnapPreviewUpdate(diagram);
                return false;
            }

            if (event->type() == QEvent::MouseButtonRelease)
            {
                if (mouse_event->button() != Qt::LeftButton) {
                    return false;
                }

                m_pointer_watchdog.stop();

                // Always stop QET's native dashed preview ourselves. Native
                // Terminal::mouseReleaseEvent will also do it when it receives
                // the event; the duplicate call is harmless and closes the
                // cases where release occurs outside the terminal/view.
                diagram->setConductor(false);

                // A terminal under the cursor remains a native QET connection.
                Terminal *release_terminal = terminalAt(diagram, scene_pos);
                if (release_terminal && release_terminal != m_source)
                {
                    resetDrag();
                    return false;
                }

                SnapCandidate candidate = findSnapCandidate(
                        m_source,
                        scene_pos,
                        m_snap_radius,
                        m_snap_segments);

                // Small release hysteresis: if the cable was visibly snapped
                // immediately before release, do not lose the branch because
                // the final OS mouse sample landed a few pixels outside the
                // hover radius.
                if (!candidate.isValid() && m_active_snap.isValid()
                        && QLineF(scene_pos, m_active_snap.scenePoint).length()
                           <= m_snap_radius * kReleaseHysteresisFactor)
                {
                    candidate = m_active_snap;
                }

                if (!candidate.isValid())
                {
                    resetDrag();
                    return false;
                }

                // Do not swallow the release: QGraphicsScene may still need it
                // to finish its mouse grab. Create the branch after native event
                // processing has completed.
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
        void beginDrag(Terminal *source,
                       Diagram *diagram,
                       QGraphicsView *view)
        {
            if (!source || !diagram || !view) {
                return;
            }

            m_source = source;
            m_diagram = diagram;
            m_view = view;
            m_recent_diagram = diagram;
            m_snap_radius = sceneSnapRadius(view);
            m_snap_segments = buildSnapSegments(diagram, source);

            if (!m_pointer_watchdog.isActive()) {
                m_pointer_watchdog.start();
            }
        }

        void scheduleSnapPreviewUpdate(Diagram *diagram)
        {
            if (!diagram || m_preview_update_pending) {
                return;
            }

            m_preview_update_pending = true;
            const QPointer<Diagram> diagram_guard = diagram;
            QTimer::singleShot(0, this, [this, diagram_guard]() {
                m_preview_update_pending = false;
                if (diagram_guard
                        && m_diagram == diagram_guard
                        && m_active_snap.isValid())
                {
                    diagram_guard->setConductorStop(
                            m_active_snap.scenePoint);
                }
            });
        }

        void clearSnapHighlight()
        {
            if (m_highlighted_conductor) {
                m_highlighted_conductor->setHighlighted(m_previous_highlight);
            }
            m_highlighted_conductor = nullptr;
            m_previous_highlight = Conductor::None;
            m_active_snap = SnapCandidate();
        }

        void setSnapHighlight(const SnapCandidate &candidate)
        {
            m_active_snap = candidate;
            if (m_highlighted_conductor == candidate.conductor) {
                return;
            }

            if (m_highlighted_conductor) {
                m_highlighted_conductor->setHighlighted(m_previous_highlight);
            }

            m_highlighted_conductor = candidate.conductor;
            m_previous_highlight = Conductor::None;
            if (m_highlighted_conductor)
            {
                m_previous_highlight = m_highlighted_conductor->highlight();
                m_highlighted_conductor->setHighlighted(Conductor::Normal);
            }
        }

        void resetDrag()
        {
            m_pointer_watchdog.stop();
            clearSnapHighlight();
            m_snap_segments.clear();
            m_snap_radius = 12.0;
            m_preview_update_pending = false;
            m_source = nullptr;
            m_diagram = nullptr;
            m_view = nullptr;
        }

        void cancelTrackedPreview()
        {
            QPointer<Diagram> diagram = m_diagram
                    ? m_diagram
                    : m_recent_diagram;
            resetDrag();
            if (diagram) {
                diagram->setConductor(false);
            }
        }

    private:
        QPointer<Terminal> m_source;
        QPointer<Diagram> m_diagram;
        QPointer<Diagram> m_recent_diagram;
        QPointer<QGraphicsView> m_view;
        QPointer<Conductor> m_highlighted_conductor;
        Conductor::Highlight m_previous_highlight = Conductor::None;
        SnapCandidate m_active_snap;
        QVector<SnapSegment> m_snap_segments;
        QTimer m_pointer_watchdog;
        qreal m_snap_radius = 12.0;
        bool m_preview_update_pending = false;
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