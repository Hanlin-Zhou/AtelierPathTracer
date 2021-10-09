#include "UIRenderer.hpp"

namespace APT {
	UIRenderer::UIRenderer(std::shared_ptr<RenderEngine> renderengine)
	{
		mHideUI = false;
		mRenderEngine = renderengine;
		mUIDescriptorHeap = std::make_unique<DX::DescriptorHeap>(*mRenderEngine->mDevice.get(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(mRenderEngine->mHWND);
		ImGui_ImplDX12_Init(mRenderEngine->mDevice->GetDevice(), mRenderEngine->mNumFrames, DXGI_FORMAT_R8G8B8A8_UNORM, mUIDescriptorHeap->GetDescriptorHeap(),
			mUIDescriptorHeap->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
			mUIDescriptorHeap->GetDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	}


	void UIRenderer::Render()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		// test
		{
			static int counter = 0;

			ImGui::Begin("Hello, world!");

			if (ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		CD3DX12_CPU_DESCRIPTOR_HANDLE UIrtv = mRenderEngine->mDescriptorHeap->GetCPUDescriptorHandle(mRenderEngine->mCurrentBuffer);
		mRenderEngine->mCommandList->GetCommandList()->OMSetRenderTargets(1, &UIrtv, 0, nullptr);
		ID3D12DescriptorHeap* const descriptorHeapList[] = {mUIDescriptorHeap->GetDescriptorHeap()};
		mRenderEngine->mCommandList->GetCommandList()->SetDescriptorHeaps(1, descriptorHeapList);
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), mRenderEngine->mCommandList->GetCommandList());

	}


	void UIRenderer::ToggleUI()
	{
		mHideUI = !mHideUI;
	}

	UIRenderer::~UIRenderer()
	{
		mRenderEngine.reset();
		OutputDebugString(L"Destroying UI Renderer---\n");
	}

}