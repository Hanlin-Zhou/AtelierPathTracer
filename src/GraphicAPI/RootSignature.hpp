#pragma once
#include <DirectX12/d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <GraphicAPI/GraphicAPIUtility.hpp>
#include <GraphicAPI/RootParameter.hpp>
#include <GraphicAPI/RootSignatureFlag.hpp>
#include <GraphicAPI/Device.hpp>
#include <vector>
using namespace Microsoft::WRL;

namespace DX {
	class RootSignature {
	public:
		RootSignature();
		void AddParameter(RootParameter parameter);
		void Init(Device device, RootSignatureFlag flag);
		ComPtr<ID3D12RootSignature> GetRootSignature() const;

	private:
		ComPtr<ID3D12RootSignature> mRootSignature;
		std::vector<CD3DX12_ROOT_PARAMETER1> mRootParameters;
		bool mInited;
	};
}