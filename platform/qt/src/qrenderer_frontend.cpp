#include "qrenderer_frontend.hpp"

#include <mbgl/map/backend_scope.hpp>
#include <mbgl/renderer/renderer.hpp>

QRendererFrontend::QRendererFrontend(mbgl::Backend& backend_, mbgl::View& view_)
    : backend(backend_)
    , view(view_) {
}

QRendererFrontend::~QRendererFrontend() {
    mbgl::BackendScope guard { backend, mbgl::BackendScope::ScopeType::Implicit };
    renderer.reset();
}

void QRendererFrontend::update(std::shared_ptr<mbgl::UpdateParameters> updateParameters_) {
    updateParameters = updateParameters_;
    emit updated();
}

std::vector<mbgl::Feature> QRendererFrontend::queryRenderedFeatures(std::shared_ptr<mbgl::RenderedQueryParameters> params) const {
    if (!renderer) return {};
    return renderer->queryRenderedFeatures(*params);
}

std::vector<mbgl::Feature> QRendererFrontend::querySourceFeatures(std::shared_ptr<mbgl::SourceQueryParameters> params) const {
    if (!renderer) return {};
    return renderer->querySourceFeatures(*params);
}

void QRendererFrontend::setRenderer(std::unique_ptr<mbgl::Renderer> renderer_, mbgl::RendererObserver& observer_) {
    renderer = std::move(renderer_);
    renderer->setObserver(&observer_);
}

void QRendererFrontend::render() {
    if (!renderer || !updateParameters) return;
    renderer->render(backend, view, *updateParameters);
}

void QRendererFrontend::onLowMemory() {
    if (!renderer) return;
    renderer->onLowMemory();
}

void QRendererFrontend::dumpDebugLogs() {
    if (!renderer) return;
    renderer->dumpDebugLogs();
}
