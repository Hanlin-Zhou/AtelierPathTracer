#include "PathTracer.hpp"
namespace APT {
	PathTracer::PathTracer(std::shared_ptr<RenderEngine> renderengine)
	{
		mScene = std::make_shared<Scene>();
		mCamera = std::make_shared<PerspectiveCamera>();
		mPreviewRenderer = std::make_shared<PreviewRenderer>(renderengine, mCamera);
		mSceneLoader = std::make_unique<SceneLoader>(mScene, mPreviewRenderer);
		
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
		mPreviewRenderer->RenderScene(*mScene);
	}
}