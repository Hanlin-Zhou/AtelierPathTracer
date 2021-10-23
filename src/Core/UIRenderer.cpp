#include "UIRenderer.hpp"

namespace APT {
	UIRenderer::UIRenderer(std::shared_ptr<RenderEngine> renderengine, std::shared_ptr<PathTracer> pathtracer)
	{
		mHideUI = false;
		mRenderEngine = renderengine;
		mPathTracer = pathtracer;
		mUIDescriptorHeap = std::make_unique<DX::ShaderDescriptorHeap>(*mRenderEngine->mDevice.get(), 1);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		LoadStyle();
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
		RenderMenuBar();
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
		CD3DX12_CPU_DESCRIPTOR_HANDLE rendertarget = mRenderEngine->mDescriptorHeap->GetCPUDescriptorHandle(mRenderEngine->mCurrentBuffer);
		mRenderEngine->mCommandList->GetCommandList()->OMSetRenderTargets(1, &rendertarget, 0, nullptr);
		ID3D12DescriptorHeap* const descriptorHeapList[] = {mUIDescriptorHeap->GetDescriptorHeap()};
		mRenderEngine->mCommandList->GetCommandList()->SetDescriptorHeaps(1, descriptorHeapList);
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), mRenderEngine->mCommandList->GetCommandList());

	}


	void UIRenderer::ToggleUI()
	{
		mHideUI = !mHideUI;
	}


	void UIRenderer::ShutDown()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void UIRenderer::LoadStyle()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		io.Fonts->AddFontFromFileTTF("Resource/Font/calibril.ttf", 16);
	}

	void UIRenderer::RenderMenuBar()
	{
		ImGui::BeginMainMenuBar();
		UI::FileMenu(mPathTracer);
		ImGui::EndMainMenuBar();
	}


	UIRenderer::~UIRenderer()
	{
	}

}