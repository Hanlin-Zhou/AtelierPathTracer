#include "Resource.hpp"

namespace DX {
	


	Resource::Resource()
	{
	}

	Resource::Resource(const ComPtr<ID3D12Resource>& resource)
	{
		mResource = resource;
		mDescriptor = mResource->GetDesc();
		mCompleted = true;
	}


	void Resource::Reset()
	{
		mResource.Reset();
		mDescriptor = D3D12_RESOURCE_DESC{};
		mCompleted = false;
	}


	void Resource::Set(ComPtr<ID3D12Resource> resource)
	{
		mResource = resource;
		mDescriptor = mResource->GetDesc();
		mCompleted = true;
	}


	ID3D12Resource* Resource::GetResource() const
	{
		return mResource.Get();
	}


	bool Resource::IsCompleted()
	{
		return mCompleted;
	}


	D3D12_GPU_VIRTUAL_ADDRESS Resource::GetGPUVirtualAddress()
	{
		return mResource->GetGPUVirtualAddress();
	}
}

