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


	/*void Device::CreateRenderTargetView(const Resource& resource, const DescriptorHeap &descriptorheap, int index)
	{
		mDevice->CreateRenderTargetView(resource.GetResource(), nullptr, descriptorheap.GetCPUDescriptorHandle(index));
	}*/
}

