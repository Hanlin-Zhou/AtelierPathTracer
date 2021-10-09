#pragma once
#include <DirectX12/d3d12.h>
#include <wrl.h>
#include <GraphicAPI/Adapter.hpp>
#include <GraphicAPI/GraphicAPIUtility.hpp>

using namespace Microsoft::WRL;

namespace DX {
	class Device {
	public:
		Device(const Adapter &adapter);

		ID3D12Device5* GetDevice() const;

	protected:
		ComPtr<ID3D12Device5> mDevice;
	};
}