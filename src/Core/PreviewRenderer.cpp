#include "PreviewRenderer.hpp"
namespace APT {
	PreviewRenderer::PreviewRenderer(const RenderEngine& renderEnigne)
	{
		//mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(renderEnigne.mClientWidth), static_cast<float>(renderEnigne.mClientHeight));
		//mScissorRect = CD3DX12_RECT(0, 0, LONG_MAX, LONG_MAX);
		//mFov = 45.0;
		//struct VertexPosColor
		//{
		//	DirectX::XMFLOAT3 Position;
		//	DirectX::XMFLOAT3 Color;
		//};
		//static VertexPosColor g_Vertices[8] = {
		//{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 0
		//{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) }, // 1
		//{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) }, // 2
		//{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) }, // 3
		//{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) }, // 4
		//{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f) }, // 5
		//{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) }, // 6
		//{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f) }  // 7
		//	};
		//static WORD g_Indicies[36] =
		//{
		//	0, 1, 2, 0, 2, 3,
		//	4, 6, 5, 4, 7, 6,
		//	4, 5, 1, 4, 1, 0,
		//	3, 2, 6, 3, 6, 7,
		//	1, 5, 6, 1, 6, 2,
		//	4, 0, 3, 4, 3, 7
		//};

		////---Vertex
		//size_t vNum = _countof(g_Vertices);
		//size_t vSize = sizeof(VertexPosColor);
		//
		//renderEnigne.Device()->CreateCommittedResource(D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, vNum* vSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_COPY_DEST, *mVertexBuffer);

		//DX::Resource intermediateVertexResource;
		//renderEnigne.Device()->CreateCommittedResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_NONE, vNum* vSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, intermediateVertexResource);

		//D3D12_SUBRESOURCE_DATA subresourceVertexData = {};
		//subresourceVertexData.pData = g_Vertices;
		//subresourceVertexData.RowPitch = vNum * vSize;
		//subresourceVertexData.SlicePitch = subresourceVertexData.RowPitch;
		//renderEnigne.UpdateSubresources(mVertexBuffer->GetResource(), intermediateVertexResource.GetResource(), &subresourceVertexData);

		//mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
		//mVertexBufferView.SizeInBytes = sizeof(g_Vertices);
		//mVertexBufferView.StrideInBytes = sizeof(VertexPosColor);

		////---Index
		//size_t iNum = _countof(g_Indicies);
		//size_t iSize = sizeof(WORD);

		//renderEnigne.Device()->CreateCommittedResource(D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, iNum* iSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_COPY_DEST, *mIndexBuffer);

		//DX::Resource intermediateIndexResource;
		//renderEnigne.Device()->CreateCommittedResource(D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_NONE, iNum* iSize, D3D12_RESOURCE_FLAG_NONE, D3D12_RESOURCE_STATE_GENERIC_READ, intermediateIndexResource);

		//D3D12_SUBRESOURCE_DATA subresourceIndexData = {};
		//subresourceIndexData.pData = g_Indicies;
		//subresourceIndexData.RowPitch = iNum * iSize;
		//subresourceIndexData.SlicePitch = subresourceIndexData.RowPitch;
		//renderEnigne.UpdateSubresources(mIndexBuffer->GetResource(), intermediateIndexResource.GetResource(), &subresourceIndexData);

		//mIndexBufferView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
		//mIndexBufferView.Format = DXGI_FORMAT_R16_UINT;
		//mIndexBufferView.SizeInBytes = sizeof(g_Indicies);

		////---DSV
		//mDSVHeap = std::make_unique<DX::DescriptorHeap>(renderEnigne.Device(), D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1);

		//// Load the vertex shader.
		//ComPtr<ID3DBlob> vertexShaderBlob;
		//DX::ThrowIfFailed(D3DReadFileToBlob(L"VertexShader.cso", &vertexShaderBlob));

		//// Load the pixel shader.
		//ComPtr<ID3DBlob> pixelShaderBlob;
		//DX::ThrowIfFailed(D3DReadFileToBlob(L"PixelShader.cso", &pixelShaderBlob));

		//D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		//{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		//	};

		//D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};
		//featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
		//D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
		//	D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		//	D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		//	D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		//	D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		//	D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

		//CD3DX12_ROOT_PARAMETER1 rootParameters[1];
		//rootParameters[0].InitAsConstants(sizeof(DirectX::XMMATRIX) / 4, 0, 0, D3D12_SHADER_VISIBILITY_VERTEX);

		//CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDescription;
		//rootSignatureDescription.Init_1_1(_countof(rootParameters), rootParameters, 0, nullptr, rootSignatureFlags);

		//// Serialize the root signature.
		//ComPtr<ID3DBlob> rootSignatureBlob;
		//ComPtr<ID3DBlob> errorBlob;
		//DX::ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDescription,
		//	featureData.HighestVersion, &rootSignatureBlob, &errorBlob));
		//// Create the root signature.
		//DX::ThrowIfFailed(renderEnigne.Device()->GetDevice()->CreateRootSignature(0, rootSignatureBlob->GetBufferPointer(),
		//	rootSignatureBlob->GetBufferSize(), IID_PPV_ARGS(&m_RootSignature)));

		//struct PipelineStateStream
		//{
		//	CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;
		//	CD3DX12_PIPELINE_STATE_STREAM_INPUT_LAYOUT InputLayout;
		//	CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;
		//	CD3DX12_PIPELINE_STATE_STREAM_VS VS;
		//	CD3DX12_PIPELINE_STATE_STREAM_PS PS;
		//	CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;
		//	CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;
		//} pipelineStateStream;

		//D3D12_RT_FORMAT_ARRAY rtvFormats = {};
		//rtvFormats.NumRenderTargets = 1;
		//rtvFormats.RTFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		//pipelineStateStream.pRootSignature = m_RootSignature.Get();
		//pipelineStateStream.InputLayout = { inputLayout, _countof(inputLayout) };
		//pipelineStateStream.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		//pipelineStateStream.VS = CD3DX12_SHADER_BYTECODE(vertexShaderBlob.Get());
		//pipelineStateStream.PS = CD3DX12_SHADER_BYTECODE(pixelShaderBlob.Get());
		//pipelineStateStream.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		//pipelineStateStream.RTVFormats = rtvFormats;

		//D3D12_PIPELINE_STATE_STREAM_DESC pipelineStateStreamDesc = {
		//sizeof(PipelineStateStream), &pipelineStateStream
		//};
		//DX::ThrowIfFailed(renderEnigne.Device()->GetDevice()->CreatePipelineState(&pipelineStateStreamDesc, IID_PPV_ARGS(&m_PipelineState)));

		//D3D12_CLEAR_VALUE optimizedClearValue = {};
		//optimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		//optimizedClearValue.DepthStencil = { 1.0f, 0 };

		//ThrowIfFailed(device->CreateCommittedResource(
		//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		//	D3D12_HEAP_FLAG_NONE,
		//	&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, width, height,
		//		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
		//	D3D12_RESOURCE_STATE_DEPTH_WRITE,
		//	&optimizedClearValue,
		//	IID_PPV_ARGS(&m_DepthBuffer)));

		//D3D12_DEPTH_STENCIL_VIEW_DESC dsv = {};
		//dsv.Format = DXGI_FORMAT_D32_FLOAT;
		//dsv.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		//dsv.Texture2D.MipSlice = 0;
		//dsv.Flags = D3D12_DSV_FLAG_NONE;

		//device->CreateDepthStencilView(m_DepthBuffer.Get(), &dsv,
		//	m_DSVHeap->GetCPUDescriptorHandleForHeapStart());
	}


	void PreviewRenderer::Render()
	{
	}
}