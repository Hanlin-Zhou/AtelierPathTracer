#pragma once
#include <Core/PreviewRenderer.hpp>
#include <memory>
namespace APT {
	class PathTracer {
	public: 
		PathTracer();
	private:
		std::unique_ptr<PreviewRenderer> mPreviewRenderer;

	};
}
