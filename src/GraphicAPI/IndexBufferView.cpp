#include "IndexBufferView.hpp"
namespace DX {
	IndexBufferView::IndexBufferView(std::unique_ptr<Resource> resource, std::unique_ptr<Resource> intermediate, UINT inputSize)
	{
		mResource = std::move(resource);
		mIntermediateResource = std::move(intermediate);
		mView.BufferLocation = mResource->GetGPUVirtualAddress();
		mView.Format = DXGI_FORMAT_R32_UINT;
		mView.SizeInBytes = inputSize;
	}

	D3D12_INDEX_BUFFER_VIEW* IndexBufferView::GetViewPtr() const
	{
		return (D3D12_INDEX_BUFFER_VIEW*)&mView;
	}
}