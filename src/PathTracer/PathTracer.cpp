#include "PathTracer.hpp"
namespace APT {
	PathTracer::PathTracer(std::shared_ptr<RenderEngine> renderengine)
	{
		mPreviewRenderer = std::make_unique<PreviewRenderer>(renderengine);
	}


	void PathTracer::RenderPreview()
	{
		mPreviewRenderer->Render();
	}
}