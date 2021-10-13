#include "ResourceInfo.hpp"
namespace DX {
	const D3D12_RESOURCE_DESC* ResourceInfo::GetDesc() const
	{
		return &mDescriptor;
	}


	D3D12_RESOURCE_STATES ResourceInfo::GetState() const
	{
		return mState;
	}


	const D3D12_CLEAR_VALUE* ResourceInfo::GetClearValue() const
	{
		return &mClearValue;
	}

	bool ResourceInfo::HasClearValue() const
	{
		return mHasClearValue;
	}


	ResourceInfo::ResourceInfo(ResourceState initState)
	{
		mState = (D3D12_RESOURCE_STATES)initState;
		mClearValue = {};
	}


	BufferInfo::BufferInfo(ResourceState initState, UINT64 bufferSize, ResourceFlag flag) : ResourceInfo(initState)
	{
		mDescriptor = CD3DX12_RESOURCE_DESC::Buffer(bufferSize, (D3D12_RESOURCE_FLAGS)flag);
	}


	Tex2DInfo::Tex2DInfo(ResourceState initState, ResourceFormat format, UINT width, UINT height, ResourceFlag flag,
		 UINT16 arraySize, UINT16 mipLevels, UINT sampleCount, UINT sampleQuality) : ResourceInfo(initState)
	{
		mDescriptor = CD3DX12_RESOURCE_DESC::Tex2D((DXGI_FORMAT)format, width, height, arraySize, mipLevels, sampleCount, sampleQuality, (D3D12_RESOURCE_FLAGS)flag);
		mClearValue.Format = (DXGI_FORMAT)format;
		mClearValue.DepthStencil = { 1.0f, 0 };
		mHasClearValue = true;
	}
}