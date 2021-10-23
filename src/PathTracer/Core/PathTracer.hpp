#pragma once
#include <PathTracer/Core/PreviewRenderer.hpp>
#include <memory>

namespace APT {
	class PathTracer {
	public: 
		PathTracer(std::shared_ptr<RenderEngine> renderengine);

		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		void RenderPreview();
	private:
		std::shared_ptr<Camera> mCamera;

		std::unique_ptr<PreviewRenderer> mPreviewRenderer;

	};
}
