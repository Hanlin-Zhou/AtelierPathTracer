#pragma once
#include <GraphicAPI/Resource.hpp>
#include <memory>

namespace DX {
	class IndexBufferView {
	public:
		IndexBufferView(std::unique_ptr<Resource> resource, std::unique_ptr<Resource> intermediate, UINT inputSize);
		D3D12_INDEX_BUFFER_VIEW* GetViewPtr() const;

	private:
		D3D12_INDEX_BUFFER_VIEW mView;
		std::unique_ptr<Resource> mResource;
		std::unique_ptr<Resource> mIntermediateResource;

	};
}