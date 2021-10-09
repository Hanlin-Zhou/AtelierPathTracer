#pragma once

#include <wrl.h>
#include <chrono>
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif
#include <DirectX12/d3d12.h>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/GraphicAPIUtility.hpp>

namespace DX {
	class Fence {
	public:
		Fence(const Device& device);

		ID3D12Fence* GetFence();

		HANDLE GetFenceEvent();
		uint64_t GetFenceValue() const;
		uint64_t FenceValueIncrement();
		void Wait(uint64_t value, std::chrono::milliseconds duration = std::chrono::milliseconds::max());

		void CloseHandle();

	protected:
		ComPtr<ID3D12Fence> mFence;
		HANDLE  mFenceEvent;
		uint64_t mFenceValue;
	};
}
