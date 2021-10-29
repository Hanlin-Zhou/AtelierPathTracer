#pragma once
#include <GraphicAPI/Resource.hpp>
#include <GraphicAPI/InputElement.hpp>
#include <memory>

namespace DX {
	class VertexBufferView {
	public:
		VertexBufferView(std::unique_ptr<Resource> resource, std::unique_ptr<Resource> intermediate, UINT dataSize, UINT inputSize);
		D3D12_VERTEX_BUFFER_VIEW* GetViewPtr() const;
	private:
		D3D12_VERTEX_BUFFER_VIEW mView;
		std::unique_ptr<Resource> mResource;
		std::unique_ptr<Resource> mIntermediateResource;
	};
}