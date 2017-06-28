#include "glfw_renderer_frontend.hpp"

#include <mbgl/renderer/renderer.hpp>
#include <mbgl/map/backend_scope.hpp>

GLFWRendererFrontend::GLFWRendererFrontend(GLFWView& glfwView_)
    : glfwView(glfwView_) {
        glfwView.setRenderFrontend(this);
}

GLFWRendererFrontend::~GLFWRendererFrontend() {
    mbgl::BackendScope guard { glfwView };
    renderer.reset();
}

void GLFWRendererFrontend::onLowMemory() {
    if (!renderer) return;
    renderer->onLowMemory();
}

void GLFWRendererFrontend::dumpDebugLogs() {
    if (!renderer) return;
    renderer->dumpDebugLogs();
}

void GLFWRendererFrontend::setRenderer(std::unique_ptr<mbgl::Renderer> renderer_, mbgl::RendererObserver& observer) {
    renderer = std::move(renderer_);
    renderer->setObserver(&observer);
}

void GLFWRendererFrontend::update(std::shared_ptr<mbgl::UpdateParameters> params) {
    updateParameters = std::move(params);
    glfwView.invalidate();
}

void GLFWRendererFrontend::render() {

    if (!updateParameters) {
        return;
    }

    renderer->render(glfwView, glfwView, *updateParameters);
}

std::vector<mbgl::Feature> GLFWRendererFrontend::queryRenderedFeatures(
        std::shared_ptr<mbgl::RenderedQueryParameters> params) const {
    return renderer->queryRenderedFeatures(*params);
}

std::vector<mbgl::Feature> GLFWRendererFrontend::querySourceFeatures(
        std::shared_ptr<mbgl::SourceQueryParameters> params) const {
    return renderer->querySourceFeatures(*params);
}
