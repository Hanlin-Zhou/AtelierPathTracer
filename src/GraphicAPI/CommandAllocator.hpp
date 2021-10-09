#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <Windows.h>
#include <GraphicAPI/Device.hpp>

namespace DX {
	class CommandAllocator {
	public:
		CommandAllocator(const Device& device, D3D12_COMMAND_LIST_TYPE type);
		ID3D12CommandAllocator* GetCommandAllocator() const;
		void Reset();
	
	protected:
		ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	};
}

