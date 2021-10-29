#pragma once
#include <DirectX12/d3d12.h>
#include <dxgi1_6.h>
#include <GraphicAPI/GraphicAPIUtility.hpp>
#include <GraphicAPI/Device.hpp>
#include <GraphicAPI/TopologyType.hpp>
#include <GraphicAPI/Shader.hpp>
#include <GraphicAPI/ResourceFormat.hpp>
#include <GraphicAPI/RootSignature.hpp>
#include <GraphicAPI/InputElement.hpp>

using namespace Microsoft::WRL;

namespace DX {

	struct PipelineStateStream {
		CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;
		CD3DX12_PIPELINE_STATE_STREAM_INPUT_LAYOUT InputLayout;
		CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;
		CD3DX12_PIPELINE_STATE_STREAM_VS VS;
		CD3DX12_PIPELINE_STATE_STREAM_PS PS;
		CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;
		CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;
	};

	class PipelineState {
	public:
		PipelineState();
		void SetTopology(TopologyType type);
		void SetVertexShader(const VertexShader& vertexShader);
		void SetPixelShader(const PixelShader& pixelShader);
		void SetDSVFormat(ResourceFormat format);
		void SetRootSignature(const RootSignature& rootSignature);
		void SetRTVFormat(ResourceFormat format);
		void Init(const Device& device);
		ComPtr<ID3D12PipelineState> GetPiplelineState();
	private:
		ComPtr<ID3D12PipelineState> mPipelineState;
		PipelineStateStream mPipelineStateStream;
		bool mInited = false;
	};
}