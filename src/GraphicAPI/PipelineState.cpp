#include "PipelineState.hpp"


namespace DX {
	PipelineState::PipelineState() {}

	void PipelineState::SetTopology(TopologyType type)
	{
		mPipelineStateStream.PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)type;
	}

	void PipelineState::SetVertexShader(const VertexShader& vertexShader)
	{
		mPipelineStateStream.VS = vertexShader.GetBytecode();
	}

	void PipelineState::SetPixelShader(const PixelShader& pixelShader)
	{
		mPipelineStateStream.PS = pixelShader.GetBytecode();
	}

	void PipelineState::SetDSVFormat(ResourceFormat format)
	{
		mPipelineStateStream.DSVFormat = (DXGI_FORMAT)format;
	}

	void PipelineState::SetRootSignature(const RootSignature& rootSignature)
	{
		mPipelineStateStream.pRootSignature = rootSignature.GetRootSignature().Get();
	}

	void PipelineState::SetRTVFormat(ResourceFormat format)
	{
		D3D12_RT_FORMAT_ARRAY rtvFormats = {};
		rtvFormats.NumRenderTargets = 1;
		rtvFormats.RTFormats[0] = (DXGI_FORMAT)format;
		mPipelineStateStream.RTVFormats = rtvFormats;
	}

	void PipelineState::Init(const Device& device)
	{
		//extern D3D12_INPUT_ELEMENT_DESC InputLayout[];
		//extern UINT InputLayoutSize;
		mPipelineStateStream.InputLayout = { DX::InputLayout, InputLayoutSize};
		D3D12_PIPELINE_STATE_STREAM_DESC pipelineStateStreamDesc = {
		sizeof(PipelineStateStream), & mPipelineStateStream
		};
		DX::ThrowIfFailed(device.GetDevice()->CreatePipelineState(&pipelineStateStreamDesc, IID_PPV_ARGS(&mPipelineState)));
	}

	ComPtr<ID3D12PipelineState> PipelineState::GetPiplelineState()
	{
		return mPipelineState;
	}

}