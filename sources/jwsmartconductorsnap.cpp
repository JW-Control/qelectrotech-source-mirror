/*
    JW Control extension for QElectroTech

    Smart Snap V2 deliberately avoids a global qApp event filter. Geometry and
    routing helpers still live in jwsmartconductorsnaplegacy.cpp, but the legacy
    automatic installer is suppressed. V2 owns its event state and listens only
    to DiagramView and its viewport.
*/

#include "diagramview.h"

#include <QApplication>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLineF>
#include <QMouseEvent>
#include <QPointer>
#include <QTimer>

// Suppress the legacy qApp-wide startup hook. The helper functions/types in
// the legacy implementation remain available in this translation unit.
#ifdef Q_COREAPP_STARTUP_FUNCTION
#undef Q_COREAPP_STARTUP_FUNCTION
#endif
#define Q_COREAPP_STARTUP_FUNCTION(AFUNC)
#include "jwsmartconductorsnaplegacy.cpp"
#undef Q_COREAPP_STARTUP_FUNCTION

namespace {

constexpr int kV2SnapRadiusPixels = 16;
constexpr qreal kV2HoverHysteresisFactor = 1.25;
constexpr qreal kV2ReleaseHysteresisFactor = 1.45;
constexpr int kV2PointerWatchdogMs = 60;

qreal v2SceneSnapRadius(QGraphicsView *view)
{
    if (!view) {
        return 12.0;
    }

    const QPointF p0 = view->mapToScene(QPoint(0, 0));
    const QPointF px = view->mapToScene(QPoint(kV2SnapRadiusPixels, 0));
    return qMax<qreal>(QLineF(p0, px).length(), 1.0);
}

class JwSmartConductorSnapV2Filter final : public QObject
{
    public:
        explicit JwSmartConductorSnapV2Filter(QObject *parent = nullptr) :
            QObject(parent)
        {
            m_pointer_watchdog.setInterval(kV2PointerWatchdogMs);
            connect(&m_pointer_watchdog, &QTimer::timeout, this, [this]() {
                if (!m_source)
                {
                    m_pointer_watchdog.stop();
                    return;
                }

                if (QApplication::mouseButtons() & Qt::LeftButton) {
                    return;
                }

                // Windows may steal MouseButtonRelease during screenshots or
                // app switching. This watchdog only exists after a verified
                // press on a pre-existing Terminal inside a DiagramView.
                cancelTrackedPreview();
            });
        }

    protected:
        bool eventFilter(QObject *watched, QEvent *event) override
        {
            if (!event) {
                return false;
            }

            if (m_source
                    && (event->type() == QEvent::WindowDeactivate
                        || event->type() == QEvent::FocusOut
                        || event->type() == QEvent::Hide
                        || event->type() == QEvent::UngrabMouse))
            {
                cancelTrackedPreview();
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

                const QPointF scene_pos = scenePositionForEvent(
                        watched, view, mouse_event);
                QPointer<Terminal> pressed_terminal =
                        terminalAt(diagram, scene_pos);
                if (!pressed_terminal)
                {
                    ++m_probe_generation;
                    return false;
                }

                if (m_source) {
                    cancelTrackedPreview();
                }

                const quint64 probe_generation = ++m_probe_generation;
                const QPointer<Diagram> diagram_guard = diagram;
                const QPointer<QGraphicsView> view_guard = view;

                // Terminal::mousePressEvent() is QET's native wire-start
                // operation: it calls setConductorStart/Stop and enables the
                // dashed conductor preview. Because this filter sees the press
                // before the scene item does, defer one event-loop turn and
                // then arm V2 from the exact Terminal that was already under
                // the cursor. We intentionally do NOT depend on mouseGrabberItem
                // here; that grabber is transient on Windows/Qt5 and caused the
                // remaining occasional missed starts in the first V2 build.
                QTimer::singleShot(0, this,
                    [this,
                     probe_generation,
                     diagram_guard,
                     view_guard,
                     pressed_terminal]() {
                        if (probe_generation != m_probe_generation
                                || m_source
                                || !diagram_guard
                                || !view_guard
                                || !pressed_terminal
                                || pressed_terminal->diagram() != diagram_guard)
                        {
                            return;
                        }

                        beginDrag(pressed_terminal,
                                  diagram_guard.data(),
                                  view_guard.data());
                    });
                return false;
            }

            if (!m_source || !m_diagram || !m_view)
            {
                if (event->type() == QEvent::MouseButtonRelease
                        && mouse_event->button() == Qt::LeftButton)
                {
                    // Invalidate a queued press that was released before V2
                    // armed itself. Never touch QET's preview in this branch.
                    ++m_probe_generation;
                }
                return false;
            }

            Diagram *diagram = m_diagram.data();
            QGraphicsView *view = m_view.data();
            if (!diagram || !view)
            {
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

                Terminal *hover_terminal = terminalAt(diagram, scene_pos);
                if (hover_terminal && hover_terminal != m_source)
                {
                    clearSnapHighlight();
                    return false;
                }

                SnapCandidate candidate = findSnapCandidate(
                        m_source,
                        scene_pos,
                        m_snap_radius,
                        m_snap_segments);

                // A small sticky band prevents the highlight from flickering
                // when the pointer lands exactly on the edge of the capture
                // radius between two Windows mouse samples.
                if (!candidate.isValid()
                        && m_active_snap.isValid()
                        && QLineF(scene_pos, m_active_snap.scenePoint).length()
                           <= m_snap_radius * kV2HoverHysteresisFactor)
                {
                    candidate = m_active_snap;
                }

                if (!candidate.isValid())
                {
                    clearSnapHighlight();
                    return false;
                }

                setSnapHighlight(candidate);

                // Updating the native preview directly is cheap and avoids a
                // queued singleShot for every mouse sample. This keeps the
                // dashed conductor visually attached to the pointer/snap point.
                diagram->setConductorStop(m_active_snap.scenePoint);
                return false;
            }

            if (event->type() == QEvent::MouseButtonRelease)
            {
                if (mouse_event->button() != Qt::LeftButton) {
                    return false;
                }

                m_pointer_watchdog.stop();
                diagram->setConductor(false);

                Terminal *release_terminal = terminalAt(diagram, scene_pos);
                if (release_terminal && release_terminal != m_source)
                {
                    resetDrag();
                    return false;
                }

                // Be slightly more permissive on the release sample than on
                // hover. A tiny last-moment pointer jump should not discard a
                // visually obvious snap.
                SnapCandidate candidate = findSnapCandidate(
                        m_source,
                        scene_pos,
                        m_snap_radius * kV2ReleaseHysteresisFactor,
                        m_snap_segments);

                if (!candidate.isValid()
                        && m_active_snap.isValid()
                        && QLineF(scene_pos, m_active_snap.scenePoint).length()
                           <= m_snap_radius * kV2ReleaseHysteresisFactor)
                {
                    candidate = m_active_snap;
                }

                if (!candidate.isValid())
                {
                    resetDrag();
                    return false;
                }

                const QPointer<Diagram> diagram_guard = diagram;
                const QPointer<Terminal> source_guard = m_source;
                const SnapCandidate queued_candidate = candidate;
                resetDrag();

                QTimer::singleShot(0,
                    [diagram_guard, source_guard, queued_candidate]() {
                        if (diagram_guard
                                && source_guard
                                && queued_candidate.isValid())
                        {
                            addSmartBranch(diagram_guard,
                                           source_guard,
                                           queued_candidate);
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
            m_snap_radius = v2SceneSnapRadius(view);
            m_snap_segments = buildSnapSegments(diagram, source);

            if (!m_pointer_watchdog.isActive()) {
                m_pointer_watchdog.start();
            }
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
            m_source = nullptr;
            m_diagram = nullptr;
            m_view = nullptr;
            ++m_probe_generation;
        }

        void cancelTrackedPreview()
        {
            QPointer<Diagram> diagram = m_diagram;
            resetDrag();
            if (diagram) {
                diagram->setConductor(false);
            }
        }

    private:
        QPointer<Terminal> m_source;
        QPointer<Diagram> m_diagram;
        QPointer<QGraphicsView> m_view;
        QPointer<Conductor> m_highlighted_conductor;
        Conductor::Highlight m_previous_highlight = Conductor::None;
        SnapCandidate m_active_snap;
        QVector<SnapSegment> m_snap_segments;
        QTimer m_pointer_watchdog;
        qreal m_snap_radius = 12.0;
        quint64 m_probe_generation = 0;
};

class JwSmartConductorSnapViewBinder final : public QObject
{
    public:
        explicit JwSmartConductorSnapViewBinder(
                JwSmartConductorSnapV2Filter *filter,
                QObject *parent = nullptr) :
            QObject(parent),
            m_filter(filter)
        {
            m_scan_timer.setInterval(600);
            m_scan_timer.setSingleShot(false);
            connect(&m_scan_timer, &QTimer::timeout,
                    this, [this]() { bindAvailableDiagramViews(); });
            m_scan_timer.start();

            if (qApp)
            {
                connect(qApp, &QApplication::focusChanged,
                        this,
                        [this](QWidget *, QWidget *) {
                            bindAvailableDiagramViews();
                        });
            }

            QTimer::singleShot(0, this,
                               [this]() { bindAvailableDiagramViews(); });
        }

    private:
        void bindAvailableDiagramViews()
        {
            if (!m_filter) {
                return;
            }

            const QWidgetList widgets = QApplication::allWidgets();
            for (QWidget *widget : widgets)
            {
                auto *view = qobject_cast<DiagramView *>(widget);
                if (!view || !view->viewport()) {
                    continue;
                }

                if (view->property("jw.smartSnapV2.bound").toBool()) {
                    continue;
                }

                // Only the canvas and DiagramView itself are observed. QMenu,
                // docks, dialogs and QApplication never receive this filter.
                view->viewport()->installEventFilter(m_filter);
                view->installEventFilter(m_filter);
                view->setProperty("jw.smartSnapV2.bound", true);
            }
        }

    private:
        QPointer<JwSmartConductorSnapV2Filter> m_filter;
        QTimer m_scan_timer;
};

JwSmartConductorSnapV2Filter *s_smart_snap_v2_filter = nullptr;
JwSmartConductorSnapViewBinder *s_smart_snap_view_binder = nullptr;
bool s_smart_snap_v2_start_queued = false;

void startJwSmartConductorSnapV2()
{
    s_smart_snap_v2_start_queued = false;
    if (!qApp || s_smart_snap_view_binder) {
        return;
    }

    if (!s_smart_snap_v2_filter) {
        s_smart_snap_v2_filter = new JwSmartConductorSnapV2Filter(qApp);
    }

    s_smart_snap_view_binder =
            new JwSmartConductorSnapViewBinder(
                    s_smart_snap_v2_filter, qApp);
}

void installJwSmartConductorSnapV2()
{
    if (!qApp || s_smart_snap_view_binder || s_smart_snap_v2_start_queued) {
        return;
    }

    s_smart_snap_v2_start_queued = true;
    QTimer::singleShot(0, qApp, []() {
        startJwSmartConductorSnapV2();
    });
}

void registerJwSmartConductorSnapV2()
{
    // Qt 5 exposes pre-routine registration as the global qAddPreRoutine().
    qAddPreRoutine(installJwSmartConductorSnapV2);
}

} // namespace

Q_CONSTRUCTOR_FUNCTION(registerJwSmartConductorSnapV2)
