#pragma once

#include <mbgl/map/backend.hpp>
#include <mbgl/renderer/renderer_frontend.hpp>

#include <QObject>

class QRendererFrontend : public QObject, public mbgl::RendererFrontend
{
    Q_OBJECT

public:
    explicit QRendererFrontend(mbgl::Backend&, mbgl::View&);
    ~QRendererFrontend() override;

    void update(std::shared_ptr<mbgl::UpdateParameters> updateParameters_) override;
    
    std::vector<mbgl::Feature> queryRenderedFeatures(std::shared_ptr<mbgl::RenderedQueryParameters> params) const override;
    std::vector<mbgl::Feature> querySourceFeatures(std::shared_ptr<mbgl::SourceQueryParameters> params) const override;
    
    void setRenderer(std::unique_ptr<mbgl::Renderer> renderer_, mbgl::RendererObserver& observer_) override;
    
    void onLowMemory() override;
    void dumpDebugLogs() override;

public slots:
    void render();

signals:
    void updated();
    
private:
    mbgl::Backend& backend;
    mbgl::View& view;
    
    std::shared_ptr<mbgl::UpdateParameters> updateParameters;
    std::unique_ptr<mbgl::Renderer> renderer;
};
