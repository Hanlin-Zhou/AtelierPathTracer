#pragma once
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/Resource.hpp>
#include <DirectX12/d3dx12.h>


namespace DX {
	class DescriptorHeap {
	public:
		ID3D12DescriptorHeap* GetDescriptorHeap()  const;

		UINT GetDesriptorHeapSize() const;

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleStart();

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(int index);

		void CreateRenderTargetView(const Resource& resource, const Device& device, int index);

	protected:
		DescriptorHeap(const Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags);

		ComPtr<ID3D12DescriptorHeap> mDescriptorHeap;

		UINT mSize;
	};


	class ShaderDescriptorHeap : public DescriptorHeap {
	public:
		ShaderDescriptorHeap(const Device& device, uint32_t numDescriptors);
	};


	class SamplerDescriptorHeap : public DescriptorHeap {
	public:
		SamplerDescriptorHeap(const Device& device, uint32_t numDescriptors);
	};


	class RTVDescriptorHeap : public DescriptorHeap {
	public:
		RTVDescriptorHeap(const Device& device, uint32_t numDescriptors);
	};


	class DSVDescriptorHeap : public DescriptorHeap {
	public:
		DSVDescriptorHeap(const Device& device, uint32_t numDescriptors);

		void CreateDepthStencilView(const Resource& resource, const Device& device);
	};
}
