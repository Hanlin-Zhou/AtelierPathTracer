#include "PathTracer.hpp"
namespace APT {
	PathTracer::PathTracer(std::shared_ptr<RenderEngine> renderengine)
	{
		mCamera = std::make_shared<PerspectiveCamera>();
		mPreviewRenderer = std::make_unique<PreviewRenderer>(renderengine, mCamera);
		
	}

	bool PathTracer::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (mPreviewRenderer->HandleMessage(hwnd, message, wParam, lParam)) {
			return true;
		}
		return false;
	}


	void PathTracer::RenderPreview()
	{
		mPreviewRenderer->Render();
	}
}