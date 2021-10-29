#include "VertexBufferView.hpp"
namespace DX {
	VertexBufferView::VertexBufferView(std::unique_ptr<Resource> resource, std::unique_ptr<Resource> intermediate, UINT dataSize, UINT inputSize)
	{
		mResource = std::move(resource);
		mIntermediateResource = std::move(intermediate);
		mView.BufferLocation = mResource->GetGPUVirtualAddress();
		mView.SizeInBytes = dataSize;
		mView.StrideInBytes = inputSize;
	}
	D3D12_VERTEX_BUFFER_VIEW* VertexBufferView::GetViewPtr() const
	{
		return (D3D12_VERTEX_BUFFER_VIEW*)&mView;
	}
}