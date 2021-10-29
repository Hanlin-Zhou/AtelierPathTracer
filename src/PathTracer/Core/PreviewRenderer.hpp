#pragma once
#include <Windowsx.h>
#include <Core/RenderEngine.hpp>
#include <GraphicAPI/Shader.hpp>
#include <GraphicAPI/VertexBufferView.hpp>
#include <GraphicAPI/IndexBufferView.hpp>
#include <PathTracer/Acceleration/Model.hpp>
#include <PathTracer/Scene/Scene.hpp>
#include <PathTracer/Camera/PerspectiveCamera.hpp>
#include <UI/UIHandleInput.hpp>
#include <directxmath.h>
#include <Utility/OutputDebug.hpp>


namespace APT {
	class PreviewRenderer {
	public:
		PreviewRenderer(std::shared_ptr<RenderEngine> renderengine, std::shared_ptr<Camera> camera);
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool CameraControl(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void Resize();
		void RenderScene(const Scene &scene);
		void UploadModel(Model& model) const;
	private:
		// std::unique_ptr<DX::Resource> mVertexBuffer;
		// std::unique_ptr<DX::Resource> mIndexBuffer;
		std::unique_ptr<DX::Resource> mDepthBuffer;

		std::vector<DX::VertexBufferView> m_VertexBufferView;
		std::vector<DX::IndexBufferView> m_IndexBufferView;

		std::unique_ptr<DX::DSVDescriptorHeap> mDSVHeap;

		std::unique_ptr<DX::VertexShader> mVertexShader;
		std::unique_ptr<DX::PixelShader> mPixelShader;

		std::unique_ptr<DX::RootSignature> mRootSignature;
		std::unique_ptr<DX::PipelineState> mPipelineState;

		D3D12_VIEWPORT mViewport;
		D3D12_RECT mScissorRect;

		bool m_ContentLoaded;

		std::shared_ptr<RenderEngine> mRenderEngine;
		std::shared_ptr<Camera> mCamera;

		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjMatrix();

		void RenderModel(Model& model);
	};
}