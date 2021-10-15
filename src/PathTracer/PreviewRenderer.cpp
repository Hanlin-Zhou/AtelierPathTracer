#include "PreviewRenderer.hpp"
namespace APT {
	PreviewRenderer::PreviewRenderer(std::shared_ptr<RenderEngine> renderengine)
	{
		mRenderEngine = renderengine;
		mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mRenderEngine->mClientWidth), static_cast<float>(mRenderEngine->mClientHeight));
		mScissorRect = CD3DX12_RECT(0, 0, LONG_MAX, LONG_MAX);
		mFov = 45.0;
		mVertexBuffer = std::make_unique<DX::Resource>();
		mIndexBuffer = std::make_unique<DX::Resource>();
		mDepthBuffer = std::make_unique<DX::Resource>();
		struct VertexPosColor
		{
			DirectX::XMFLOAT3 Position;
			DirectX::XMFLOAT3 Color;
		};
		static VertexPosColor g_Vertices[8] = {
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 0
		{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) }, // 1
		{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) }, // 2
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) }, // 3
		{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) }, // 4
		{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f) }, // 5
		{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) }, // 6
		{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f) }  // 7
			};
		static WORD g_Indicies[36] =
		{
			0, 1, 2, 0, 2, 3,
			4, 6, 5, 4, 7, 6,
			4, 5, 1, 4, 1, 0,
			3, 2, 6, 3, 6, 7,
			1, 5, 6, 1, 6, 2,
			4, 0, 3, 4, 3, 7
		};

		//---Vertex
		size_t vNum = _countof(g_Vertices);
		size_t vSize = sizeof(VertexPosColor);
		mRenderEngine->Record();
		DX::BufferInfo VbufferInfo(DX::ResourceState::CopyDest, vNum* vSize);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, VbufferInfo, *mVertexBuffer);

		DX::Resource intermediateVertexResource;
		DX::BufferInfo VIntermediateInfo(DX::ResourceState::GenericRead, vNum* vSize);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, VIntermediateInfo, intermediateVertexResource);

		D3D12_SUBRESOURCE_DATA subresourceVertexData = {};
		subresourceVertexData.pData = g_Vertices;
		subresourceVertexData.RowPitch = vNum * vSize;
		subresourceVertexData.SlicePitch = subresourceVertexData.RowPitch;
		mRenderEngine->UpdateSubresources(mVertexBuffer->GetResource(), intermediateVertexResource.GetResource(), &subresourceVertexData);

		mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
		mVertexBufferView.SizeInBytes = sizeof(g_Vertices);
		mVertexBufferView.StrideInBytes = sizeof(VertexPosColor);

		//---Index
		size_t iNum = _countof(g_Indicies);
		size_t iSize = sizeof(WORD);

		DX::BufferInfo IBufferInfo(DX::ResourceState::CopyDest, iNum * iSize);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, IBufferInfo, *mIndexBuffer);

		DX::Resource intermediateIndexResource;
		DX::BufferInfo IIntermediateInfo(DX::ResourceState::GenericRead, iNum* iSize);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, IIntermediateInfo, intermediateIndexResource);

		D3D12_SUBRESOURCE_DATA subresourceIndexData = {};
		subresourceIndexData.pData = g_Indicies;
		subresourceIndexData.RowPitch = iNum * iSize;
		subresourceIndexData.SlicePitch = subresourceIndexData.RowPitch;
		mRenderEngine->UpdateSubresources(mIndexBuffer->GetResource(), intermediateIndexResource.GetResource(), &subresourceIndexData);

		mIndexBufferView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
		mIndexBufferView.Format = DXGI_FORMAT_R16_UINT;
		mIndexBufferView.SizeInBytes = sizeof(g_Indicies);

		//---DSV
		mDSVHeap = std::make_unique<DX::DSVDescriptorHeap>(*mRenderEngine->Device(), 1);

		mVertexShader = std::make_unique<DX::VertexShader>(L"CompiledShader/VertexShader.cso");

		mPixelShader = std::make_unique<DX::PixelShader>(L"CompiledShader/PixelShader.cso");

		D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};

		D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};
		featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
		D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

		CD3DX12_ROOT_PARAMETER1 rootParameters[1];
		rootParameters[0].InitAsConstants(sizeof(DirectX::XMMATRIX) / 4, 0, 0, D3D12_SHADER_VISIBILITY_VERTEX);

		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDescription;
		rootSignatureDescription.Init_1_1(_countof(rootParameters), rootParameters, 0, nullptr, rootSignatureFlags);

		// Serialize the root signature.
		ComPtr<ID3DBlob> rootSignatureBlob;
		ComPtr<ID3DBlob> errorBlob;
		DX::ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDescription,
			featureData.HighestVersion, &rootSignatureBlob, &errorBlob));
		// Create the root signature.
		DX::ThrowIfFailed(mRenderEngine->Device()->GetDevice()->CreateRootSignature(0, rootSignatureBlob->GetBufferPointer(),
			rootSignatureBlob->GetBufferSize(), IID_PPV_ARGS(&m_RootSignature)));

		struct PipelineStateStream
		{
			CD3DX12_PIPELINE_STATE_STREAM_ROOT_SIGNATURE pRootSignature;
			CD3DX12_PIPELINE_STATE_STREAM_INPUT_LAYOUT InputLayout;
			CD3DX12_PIPELINE_STATE_STREAM_PRIMITIVE_TOPOLOGY PrimitiveTopologyType;
			CD3DX12_PIPELINE_STATE_STREAM_VS VS;
			CD3DX12_PIPELINE_STATE_STREAM_PS PS;
			CD3DX12_PIPELINE_STATE_STREAM_DEPTH_STENCIL_FORMAT DSVFormat;
			CD3DX12_PIPELINE_STATE_STREAM_RENDER_TARGET_FORMATS RTVFormats;
		} pipelineStateStream;

		D3D12_RT_FORMAT_ARRAY rtvFormats = {};
		rtvFormats.NumRenderTargets = 1;
		rtvFormats.RTFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		pipelineStateStream.pRootSignature = m_RootSignature.Get();
		pipelineStateStream.InputLayout = { inputLayout, _countof(inputLayout) };
		pipelineStateStream.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		pipelineStateStream.VS = mVertexShader->GetBytecode();
		pipelineStateStream.PS = mPixelShader->GetBytecode();
		pipelineStateStream.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		pipelineStateStream.RTVFormats = rtvFormats;

		D3D12_PIPELINE_STATE_STREAM_DESC pipelineStateStreamDesc = {
		sizeof(PipelineStateStream), &pipelineStateStream
		};
		DX::ThrowIfFailed(mRenderEngine->Device()->GetDevice()->CreatePipelineState(&pipelineStateStreamDesc, IID_PPV_ARGS(&m_PipelineState)));

		DX::Tex2DInfo DSInfo(DX::ResourceState::DepthWrite, DX::ResourceFormat::Depth32, mRenderEngine->GetWidth(), mRenderEngine->GetHeight(), DX::ResourceFlag::AllowDS);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, DSInfo, *mDepthBuffer);

		mDSVHeap->CreateDepthStencilView(*mDepthBuffer, *mRenderEngine->Device());

		mRenderEngine->ExcecuteAndWait();

		// Update the view matrix.
		const DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(0, 0, -10, 1);
		const DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0, 0, 0, 1);
		const DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0, 1, 0, 0);
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);

		float aspectRatio = mRenderEngine->GetWidth() / static_cast<float>(mRenderEngine->GetHeight());
		m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(mFov), aspectRatio, 0.1f, 100.0f);

		m_ModelMatrix = DirectX::XMMatrixIdentity();
	}


	void PreviewRenderer::Render()
	{
		mRenderEngine->ClearDepth(*mDSVHeap);
		mRenderEngine->CommandList()->GetCommandList()->SetPipelineState(m_PipelineState.Get());
		mRenderEngine->CommandList()->GetCommandList()->SetGraphicsRootSignature(m_RootSignature.Get());

		mRenderEngine->CommandList()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mRenderEngine->CommandList()->GetCommandList()->IASetVertexBuffers(0, 1, &mVertexBufferView);
		mRenderEngine->CommandList()->GetCommandList()->IASetIndexBuffer(&mIndexBufferView);

		mRenderEngine->CommandList()->GetCommandList()->RSSetViewports(1, &mViewport);
		mRenderEngine->CommandList()->GetCommandList()->RSSetScissorRects(1, &mScissorRect);

		CD3DX12_CPU_DESCRIPTOR_HANDLE dsv = mDSVHeap->GetCPUDescriptorHandleStart();
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv = mRenderEngine->DescriptorHeap()->GetCPUDescriptorHandle(mRenderEngine->GetCurrentBufferIndex());
		mRenderEngine->CommandList()->GetCommandList()->OMSetRenderTargets(1, &rtv, FALSE, &dsv);

		DirectX::XMMATRIX mvpMatrix = DirectX::XMMatrixMultiply(m_ModelMatrix, m_ViewMatrix);
		mvpMatrix = DirectX::XMMatrixMultiply(mvpMatrix, m_ProjectionMatrix);
		mRenderEngine->CommandList()->GetCommandList()->SetGraphicsRoot32BitConstants(0, sizeof(DirectX::XMMATRIX) / 4, &mvpMatrix, 0);

		mRenderEngine->CommandList()->GetCommandList()->DrawIndexedInstanced(36, 1, 0, 0, 0);
	}
}