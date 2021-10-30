#include "PreviewRenderer.hpp"
namespace APT {
	PreviewRenderer::PreviewRenderer(std::shared_ptr<RenderEngine> renderengine, std::shared_ptr<Camera> camera)
	{
		mCamera = camera;
		mRenderEngine = renderengine;
		mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mRenderEngine->mClientWidth), static_cast<float>(mRenderEngine->mClientHeight));
		mScissorRect = CD3DX12_RECT(0, 0, LONG_MAX, LONG_MAX);
		/*std::unique_ptr<DX::Resource> mVertexBuffer = std::make_unique<DX::Resource>();
		std::unique_ptr<DX::Resource> mColorBuffer = std::make_unique<DX::Resource>();
		std::unique_ptr<DX::Resource> mIndexBuffer = std::make_unique<DX::Resource>();*/
		mDepthBuffer = std::make_unique<DX::Resource>();
		mRenderEngine->Record();
		//static DX::VertexInput g_Vertices[8] = {
		//{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f)}, // 0
		//{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f)},  // 1
		//{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f)},  // 2
		//{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f)},  // 3
		//{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f)},  // 4
		//{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f)},  // 5
		//{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f)}, // 6
		//{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f)}  // 7
		//};

		//static DX::VertexInput g_Vertices2[8] = {
		//{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 0
		//{ DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) }, // 1
		//{ DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) }, // 2
		//{ DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) }, // 3
		//{ DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f) }, // 4
		//{ DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f) }, // 5
		//{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) }, // 6
		//{ DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f) }  // 7
		//};

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
		//size_t vSize = sizeof(DX::VertexInput);
		//mRenderEngine->Record();
		//DX::BufferInfo VbufferInfo(DX::ResourceState::CopyDest, vNum* vSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, VbufferInfo, *mVertexBuffer);

		//DX::Resource intermediateVertexResource;
		//DX::BufferInfo VIntermediateInfo(DX::ResourceState::GenericRead, vNum* vSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, VIntermediateInfo, intermediateVertexResource);

		//mRenderEngine->UpdateSubresources(*mVertexBuffer, intermediateVertexResource, g_Vertices, vNum* vSize);

		//m_VertexBufferView.push_back(DX::VertexBufferView(std::move(mVertexBuffer), sizeof(g_Vertices), sizeof(DX::VertexInput)));


		////---Color
		//size_t cNum = _countof(g_Vertices2);
		//size_t cSize = sizeof(DX::VertexInput);
		//DX::BufferInfo CbufferInfo(DX::ResourceState::CopyDest, cNum * cSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, CbufferInfo, *mColorBuffer);

		//DX::Resource intermediateColorResource;
		//DX::BufferInfo CIntermediateInfo(DX::ResourceState::GenericRead, cNum * cSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, CIntermediateInfo, intermediateColorResource);

		//mRenderEngine->UpdateSubresources(*mColorBuffer, intermediateColorResource, g_Vertices2, cNum * cSize);

		//m_VertexBufferView.push_back(DX::VertexBufferView(std::move(mColorBuffer), sizeof(g_Vertices2), sizeof(DX::VertexInput)));

		////---Index
		//size_t iNum = _countof(g_Indicies);
		//size_t iSize = sizeof(WORD);

		//DX::BufferInfo IBufferInfo(DX::ResourceState::CopyDest, iNum * iSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, IBufferInfo, *mIndexBuffer);

		//DX::Resource intermediateIndexResource;
		//DX::BufferInfo IIntermediateInfo(DX::ResourceState::GenericRead, iNum* iSize);
		//mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, IIntermediateInfo, intermediateIndexResource);

		//mRenderEngine->UpdateSubresources(*mIndexBuffer, intermediateIndexResource, g_Indicies, iNum* iSize);

		//m_IndexBufferView.push_back(DX::IndexBufferView(std::move(mIndexBuffer), sizeof(g_Indicies)));

		//---DSV
		mDSVHeap = std::make_unique<DX::DSVDescriptorHeap>(*mRenderEngine->Device(), 1);
		//---Shader
		mVertexShader = std::make_unique<DX::VertexShader>(L"CompiledShader/VertexShader.cso");
		mPixelShader = std::make_unique<DX::PixelShader>(L"CompiledShader/PixelShader.cso");

		//---RootSignature
		mRootSignature = std::make_unique<DX::RootSignature>();
		DX::RootParameter MVPmatrix(sizeof(DirectX::XMMATRIX) / 4, 0, 0, DX::ShaderVisibilityFlag::Vertex);
		mRootSignature->AddParameter(MVPmatrix);
		mRootSignature->Init(*mRenderEngine->Device(), DX::RootSignatureFlag::AllowInputLayout | DX::RootSignatureFlag::DenyHull
			| DX::RootSignatureFlag::DenyDomain | DX::RootSignatureFlag::DenyGeometry | DX::RootSignatureFlag::DenyPixel);

		//---PipelineState
		mPipelineState = std::make_unique<DX::PipelineState>();
		mPipelineState->SetRootSignature(*mRootSignature);
		mPipelineState->SetTopology(DX::TopologyType::Triangle);
		mPipelineState->SetVertexShader(*mVertexShader);
		mPipelineState->SetPixelShader(*mPixelShader);
		mPipelineState->SetDSVFormat(DX::ResourceFormat::Depth32);
		mPipelineState->SetRTVFormat(DX::ResourceFormat::RGBA8);
		mPipelineState->Init(*mRenderEngine->Device());

		//---CommandList Work
		Resize();
		mRenderEngine->ExcecuteAndWait();
	}


	void PreviewRenderer::UploadModel(Model& model) const
	{
		// mRenderEngine->Record();
		for (int i = 0; i < model.mMeshes.size(); i++)
		{
			//Index
			{
				std::unique_ptr<DX::Resource> Buffer = std::make_unique<DX::Resource>();
				size_t Size = sizeof(unsigned int) * model.mMeshes[i]->mMesh->mVertexIndices.size();
				DX::BufferInfo bufferInfo(DX::ResourceState::CopyDest, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, bufferInfo, *Buffer);
				std::unique_ptr<DX::Resource> intermediateResource = std::make_unique<DX::Resource>();
				DX::BufferInfo IntermediateInfo(DX::ResourceState::GenericRead, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, IntermediateInfo, *intermediateResource);
				mRenderEngine->UpdateSubresources(*Buffer, *intermediateResource, &model.mMeshes[i]->mMesh->mVertexIndices[0], Size);
				model.mMeshes[i]->mIndexView = std::make_unique<DX::IndexBufferView>(std::move(Buffer), std::move(intermediateResource),
					sizeof(unsigned int) * model.mMeshes[i]->mMesh->mVertexIndices.size());
			}
			//Vertex
			{
				std::unique_ptr<DX::Resource> Buffer = std::make_unique<DX::Resource>();
				size_t Size = sizeof(DX::VertexInput) * model.mMeshes[i]->mMesh->mNumVertice;
				DX::BufferInfo bufferInfo(DX::ResourceState::CopyDest, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, bufferInfo, *Buffer);
				std::unique_ptr<DX::Resource> intermediateResource = std::make_unique<DX::Resource>();
				DX::BufferInfo IntermediateInfo(DX::ResourceState::GenericRead, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, IntermediateInfo, *intermediateResource);
				mRenderEngine->UpdateSubresources(*Buffer, *intermediateResource, &model.mMeshes[i]->mMesh->mVertex[0], Size);
				model.mMeshes[i]->mVertexView = std::make_unique<DX::VertexBufferView>(std::move(Buffer), std::move(intermediateResource),
					sizeof(Vec3f) * model.mMeshes[i]->mMesh->mNumVertice, sizeof(DX::VertexInput));
			}
			//Normal
			{
				std::unique_ptr<DX::Resource> Buffer = std::make_unique<DX::Resource>();
				size_t Size = sizeof(DX::VertexInput) * model.mMeshes[i]->mMesh->mNumVertice;
				DX::BufferInfo bufferInfo(DX::ResourceState::CopyDest, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, bufferInfo, *Buffer);
				std::unique_ptr<DX::Resource> intermediateResource = std::make_unique<DX::Resource>();
				DX::BufferInfo IntermediateInfo(DX::ResourceState::GenericRead, Size);
				mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Upload, IntermediateInfo, *intermediateResource);
				mRenderEngine->UpdateSubresources(*Buffer, *intermediateResource, &model.mMeshes[i]->mMesh->mNormal[0], Size);
				model.mMeshes[i]->mNormalView = std::make_unique<DX::VertexBufferView>(std::move(Buffer), std::move(intermediateResource),
					sizeof(Vec3f) * model.mMeshes[i]->mMesh->mNumVertice, sizeof(DX::VertexInput));
			}
		}
		// mRenderEngine->ExcecuteAndWait();
	}

	void PreviewRenderer::RenderScene(const Scene& scene)
	{
		CameraWalk();
		mRenderEngine->ClearDepth(*mDSVHeap);
		mRenderEngine->CommandList()->GetCommandList()->SetPipelineState(mPipelineState->GetPiplelineState().Get());
		mRenderEngine->CommandList()->GetCommandList()->SetGraphicsRootSignature(mRootSignature->GetRootSignature().Get());
		mRenderEngine->CommandList()->GetCommandList()->RSSetViewports(1, &mViewport);
		mRenderEngine->CommandList()->GetCommandList()->RSSetScissorRects(1, &mScissorRect);
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsv = mDSVHeap->GetCPUDescriptorHandleStart();
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtv = mRenderEngine->DescriptorHeap()->GetCPUDescriptorHandle(mRenderEngine->GetCurrentBufferIndex());
		mRenderEngine->CommandList()->GetCommandList()->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
		for (int i = 0; i < scene.aggregate->mModels.size(); i++)
		{
			RenderModel(*scene.aggregate->mModels[i]);
		}


	}

	void PreviewRenderer::RenderModel(Model& model)
	{
		DirectX::XMMATRIX mvpMatrix = DirectX::XMMatrixMultiply(DirectX::XMMatrixIdentity(), GetViewMatrix());
		mvpMatrix = DirectX::XMMatrixMultiply(mvpMatrix, GetProjMatrix());
		mRenderEngine->CommandList()->GetCommandList()->SetGraphicsRoot32BitConstants(0, sizeof(DirectX::XMMATRIX) / 4, &mvpMatrix, 0);
		mRenderEngine->CommandList()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		for (int i = 0; i < model.mMeshes.size(); i++)
		{
			mRenderEngine->CommandList()->GetCommandList()->IASetIndexBuffer(model.mMeshes[i]->mIndexView->GetViewPtr());
			mRenderEngine->CommandList()->GetCommandList()->IASetVertexBuffers(0, 1, model.mMeshes[i]->mVertexView->GetViewPtr());
			mRenderEngine->CommandList()->GetCommandList()->IASetVertexBuffers(1, 1, model.mMeshes[i]->mNormalView->GetViewPtr());
			mRenderEngine->CommandList()->GetCommandList()->DrawIndexedInstanced(model.mMeshes[i]->mMesh->mVertexIndices.size(), 1, 0, 0, 0);
		}
	}


	bool PreviewRenderer::HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (CameraControl(hwnd, message, wParam, lParam)) {
			return true;
		}
		switch (message) {
		case WM_EXITSIZEMOVE:
			Resize();
		}
		return false;
	}

	bool PreviewRenderer::CameraControl(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (UIMouseCatured()) {
			return false;
		}
		static bool W_Pressed = false;
		static bool S_Pressed = false;
		static bool A_Pressed = false;
		static bool D_Pressed = false;
		static bool Q_Pressed = false;
		static bool E_Pressed = false;

		Vec3f frontDirection = Normalize(mCamera->GetTarget() - mCamera->GetPosition());
		Vec3f rightDirection = Cross(frontDirection, mCamera->GetUp());
		Vec3f upDirection = mCamera->GetUp();
		Vec3f camTarget = mCamera->GetTarget();
		Vec3f camPosition = mCamera->GetPosition();

		switch (message) {
		case WM_MOUSEMOVE:
		{
			Vec2i pos = Vec2i(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			static int lastX = pos.x;
			static int lastY = pos.y;

			switch (wParam) {
			case MK_LBUTTON:
				float hor_r = static_cast<float>(pos.x - lastX) / static_cast<float>(mRenderEngine->GetWidth()) * 150.f;
				float ver_r = static_cast<float>(pos.y - lastY) / -static_cast<float>(mRenderEngine->GetHeight()) * 150.f;
				Vec3f relativePos = camPosition - camTarget;
				Transform rotation = Transform::RotateAroundY(hor_r);
				rotation *= Transform::RotateAround(rightDirection, ver_r);
				Vec3f newPos = camTarget + rotation(relativePos);
				mCamera->SetPosition(newPos);
			}

			lastX = pos.x;
			lastY = pos.y;
		}
		case WM_KEYDOWN:
			switch (wParam) {
			case 0x57:
				// W
				mKeyInput.W = true;
				break;
			case 0x53:
				// S
				mKeyInput.S = true;
				break;
			case 0x41:
				// A
				mKeyInput.A = true;
				break;
			case 0x44:
				// A
				mKeyInput.D = true;
				break;
			case 0x10:
				// Rise
				mKeyInput.Rise = true;
				break;
			case 0x11:
				// Lower
				mKeyInput.Lower = true;
				break;
			}break;
		case WM_KEYUP:
			switch (wParam) {
			case 0x57:
				// W
				mKeyInput.W = false;
				break;
			case 0x53:
				// S
				mKeyInput.S = false;
				break;
			case 0x41:
				// A
				mKeyInput.A = false;
				break;
			case 0x44:
				// D
				mKeyInput.D = false;
				break;
			case 0x10:
				// Rise
				mKeyInput.Rise = false;
				break;
			case 0x11:
				// Lower
				mKeyInput.Lower = false;
				break;
			}break;
		
		}
		return false;
	}


	void PreviewRenderer::CameraWalk()
	{
		Vec3f frontDirection = Normalize(mCamera->GetTarget() - mCamera->GetPosition());
		Vec3f rightDirection = Cross(frontDirection, mCamera->GetUp());
		Vec3f upDirection = mCamera->GetUp();
		Vec3f camTarget = mCamera->GetTarget();
		Vec3f camPosition = mCamera->GetPosition();
		if (mKeyInput.W) {
			mCamera->SetPosition(0.1f * frontDirection + camPosition);
			mCamera->SetTarget(0.1f * frontDirection + camTarget);
		}
		else if (mKeyInput.S) {
			mCamera->SetPosition(-0.1f * frontDirection + camPosition);
			mCamera->SetTarget(-0.1f * frontDirection + camTarget);
		}
		if (mKeyInput.A) {
			mCamera->SetPosition(0.1f * rightDirection + camPosition);
			mCamera->SetTarget(0.1f * rightDirection + camTarget);
		}
		else if (mKeyInput.D) {
			mCamera->SetPosition(-0.1f * rightDirection + camPosition);
			mCamera->SetTarget(-0.1f * rightDirection + camTarget);
		}
		if (mKeyInput.Rise) {
			mCamera->SetPosition(0.1f * upDirection + camPosition);
			mCamera->SetTarget(0.1f * upDirection + camTarget);
		}
		else if (mKeyInput.Lower) {
			mCamera->SetPosition(-0.1f * upDirection + camPosition);
			mCamera->SetTarget(-0.1f * upDirection + camTarget);
		}
	}
	

	void PreviewRenderer::Resize()
	{
		DX::Tex2DInfo DSInfo(DX::ResourceState::DepthWrite, DX::ResourceFormat::Depth32, mRenderEngine->GetWidth(), mRenderEngine->GetHeight(), DX::ResourceFlag::AllowDS);
		mRenderEngine->Device()->CreateCommittedResource(DX::HeapType::Default, DSInfo, *mDepthBuffer);
		mDSVHeap->CreateDepthStencilView(*mDepthBuffer, *mRenderEngine->Device());
		mViewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(mRenderEngine->mClientWidth), static_cast<float>(mRenderEngine->mClientHeight));
	}

	DirectX::XMMATRIX PreviewRenderer::GetViewMatrix()
	{
		// Update the view matrix.
		Vec3f pos = mCamera->GetPosition();
		Vec3f target = mCamera->GetTarget();
		Vec3f up = mCamera->GetUp();
		const DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1);
		const DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(target.x, target.y, target.z, 1);
		const DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(up.x, up.y, up.z, 0);
		return DirectX::XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);
	}

	DirectX::XMMATRIX PreviewRenderer::GetProjMatrix()
	{
		CameraType t = mCamera->GetType();
		switch (t) {
		case CameraType::Perspective:
			// PerspectiveCamera* pCam = dynamic_cast<PerspectiveCamera*>(mCamera.get());
			std::shared_ptr<PerspectiveCamera> pCam;
			pCam = std::static_pointer_cast<PerspectiveCamera>(mCamera);
			return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(pCam->GetFov()), mRenderEngine->GetWidth() / static_cast<float>(mRenderEngine->GetHeight()), pCam->GetNear(), pCam->GetFar());
		}
		return DirectX::XMMatrixIdentity();
	}

}