#include "Device.hpp"

namespace DX {
	Device::Device(const Adapter& adapter)
	{
		ThrowIfFailed(D3D12CreateDevice(adapter.GetAdapter(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&mDevice)));
	}


	ID3D12Device5* Device::GetDevice() const
	{
		return mDevice.Get();
	}

	void Device::CreateCommittedResource(HeapType heapType, const ResourceInfo &info, Resource& resource)
	{
		CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES((D3D12_HEAP_TYPE)heapType);
		ComPtr<ID3D12Resource> resourcePtr;
		const D3D12_CLEAR_VALUE* clearValue = nullptr;
		if (info.HasClearValue()) clearValue = info.GetClearValue();
		ThrowIfFailed(mDevice->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			info.GetDesc(),
			info.GetState(),
			clearValue,
			IID_PPV_ARGS(&resourcePtr)));
		resource.Set(resourcePtr);
	}
}

