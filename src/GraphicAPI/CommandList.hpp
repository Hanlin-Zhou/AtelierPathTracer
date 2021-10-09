#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <Windows.h>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/CommandAllocator.hpp>
#include <GraphicAPI/ResourceBarrier.hpp>

namespace DX {
	class CommandList {
	public:
		CommandList(const Device& device, const CommandAllocator& allocator, D3D12_COMMAND_LIST_TYPE type);

		ID3D12GraphicsCommandList* GetCommandList() const;

		void SetResourceBarrier(ResourceBarrier& resourcebarrier);

		void Reset(const CommandAllocator& commandallocator);

		void ClearRenderTargetView(CD3DX12_CPU_DESCRIPTOR_HANDLE rtv, const float* color);

		void Close();

	protected:
		ComPtr<ID3D12GraphicsCommandList> mCommandList;
	};
}
