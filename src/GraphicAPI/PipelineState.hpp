#pragma once
#include <DirectX12/d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <GraphicAPI/GraphicAPIUtility.hpp>
using namespace Microsoft::WRL;


namespace DX {
	class PipelineState {
	public:
		PipelineState();
	private:
		ComPtr<ID3D12PipelineState> mPipelineState;

	};
}