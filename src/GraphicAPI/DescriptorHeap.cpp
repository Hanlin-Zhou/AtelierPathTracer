#include "DescriptorHeap.hpp"

namespace DX {
	DescriptorHeap::DescriptorHeap(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = numDescriptors;
		desc.Type = type;
		desc.Flags = flags;
		ThrowIfFailed(device.GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&mDescriptorHeap)));
		mSize = device.GetDevice()->GetDescriptorHandleIncrementSize(type);
	}


	ID3D12DescriptorHeap* DescriptorHeap::GetDescriptorHeap() const
	{
		return mDescriptorHeap.Get();
	}


	UINT DescriptorHeap::GetDesriptorHeapSize() const
	{
		return mSize;
	}


	CD3DX12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandleStart()
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(mDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	}


	CD3DX12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandle(int index)
	{
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(mDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), index, mSize);
	}


	void DescriptorHeap::CreateRenderTargetView(const Resource& resource, const Device& device, int index)
	{
		device.GetDevice()->CreateRenderTargetView(resource.GetResource(), nullptr, GetCPUDescriptorHandle(index));
	}
}