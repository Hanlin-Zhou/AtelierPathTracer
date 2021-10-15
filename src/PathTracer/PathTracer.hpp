#pragma once
#include <PathTracer/PreviewRenderer.hpp>
#include <memory>

namespace APT {
	class PathTracer {
	public: 
		PathTracer(std::shared_ptr<RenderEngine> renderengine);

		void RenderPreview();
	private:
		std::unique_ptr<PreviewRenderer> mPreviewRenderer;

	};
}
