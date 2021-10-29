#pragma once
#include <PathTracer/Core/PreviewRenderer.hpp>
#include <PathTracer/Core/SceneLoader.hpp>
#include <memory>

namespace APT {
	class PathTracer {
	public: 
		PathTracer(std::shared_ptr<RenderEngine> renderengine);

		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		void RenderPreview();
	
		std::shared_ptr<Camera> mCamera;

		std::shared_ptr<Scene> mScene;

		std::shared_ptr<PreviewRenderer> mPreviewRenderer;

		std::unique_ptr<SceneLoader> mSceneLoader;

	};
}
