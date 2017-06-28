#pragma once

#include "glfw_view.hpp"
#include <mbgl/renderer/renderer_frontend.hpp>

#include <memory>

namespace mbgl {
class Renderer;
} // namespae mbgl

class GLFWRendererFrontend : public mbgl::RendererFrontend {
public:
    GLFWRendererFrontend(GLFWView&);
    ~GLFWRendererFrontend() override;

    void update(std::shared_ptr<mbgl::UpdateParameters>) override;
    void render();

    std::vector<mbgl::Feature> queryRenderedFeatures(std::shared_ptr<mbgl::RenderedQueryParameters>) const override;

    std::vector<mbgl::Feature> querySourceFeatures(std::shared_ptr<mbgl::SourceQueryParameters>) const override;

    void setRenderer(std::unique_ptr<mbgl::Renderer>, mbgl::RendererObserver&) override;

    void onLowMemory() override;

    void dumpDebugLogs() override;

private:
    GLFWView& glfwView;
    std::unique_ptr<mbgl::Renderer> renderer;
    std::shared_ptr<mbgl::UpdateParameters> updateParameters;
};
