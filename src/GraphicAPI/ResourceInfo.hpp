#pragma once
#include <DirectX12/d3dx12.h>
#include <GraphicAPI/ResourceState.hpp>
#include <GraphicAPI/ResourceFlag.hpp>
#include <GraphicAPI/ResourceFormat.hpp>

namespace DX {
	class ResourceInfo {
	public:
		const D3D12_RESOURCE_DESC* GetDesc() const;
		D3D12_RESOURCE_STATES GetState() const;
		const D3D12_CLEAR_VALUE* GetClearValue() const;
		bool HasClearValue() const;

	protected:
		ResourceInfo(ResourceState initState);
		D3D12_RESOURCE_DESC mDescriptor;
		D3D12_RESOURCE_STATES mState;
		D3D12_CLEAR_VALUE mClearValue;
		bool mHasClearValue = false;
	};


	class BufferInfo : public ResourceInfo {
	public:
		BufferInfo(ResourceState initState, UINT64 bufferSize, ResourceFlag flag = ResourceFlag::None);

	};


	class Tex2DInfo : public ResourceInfo {
	public:
		Tex2DInfo(ResourceState initState, ResourceFormat format, UINT width, UINT height, ResourceFlag flag = ResourceFlag::None,
		 UINT16 arraySize = 1, UINT16 mipLevels = 0, UINT sampleCount = 1, UINT sampleQuality = 0);

	};

}