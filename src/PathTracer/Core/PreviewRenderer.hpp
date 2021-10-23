#pragma once
#include <Windowsx.h>
#include <Core/RenderEngine.hpp>
#include <GraphicAPI/Shader.hpp>
#include <PathTracer/Camera/PerspectiveCamera.hpp>
#include <UI/UIHandleInput.hpp>
#include <directxmath.h>
// to be deleted



namespace APT {
	class PreviewRenderer {
	public:
		PreviewRenderer(std::shared_ptr<RenderEngine> renderengine, std::shared_ptr<Camera> camera);
		bool HandleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool CameraControl(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		void Resize();
		void Render();
	private:
		std::unique_ptr<DX::Resource> mVertexBuffer;
		std::unique_ptr<DX::Resource> mIndexBuffer;
		std::unique_ptr<DX::Resource> mDepthBuffer;

		D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;
		D3D12_INDEX_BUFFER_VIEW mIndexBufferView;

		std::unique_ptr<DX::DSVDescriptorHeap> mDSVHeap;

		std::unique_ptr<DX::VertexShader> mVertexShader;
		std::unique_ptr<DX::PixelShader> mPixelShader;

		std::unique_ptr<DX::RootSignature> mRootSignature;
		ComPtr<ID3D12RootSignature> m_RootSignature;
		std::unique_ptr<DX::PipelineState> mPipelineState;
		ComPtr<ID3D12PipelineState> m_PipelineState;

		D3D12_VIEWPORT mViewport;
		D3D12_RECT mScissorRect;


		float mFov;

		DirectX::XMMATRIX m_ModelMatrix;
		DirectX::XMMATRIX m_ViewMatrix;
		DirectX::XMMATRIX m_ProjectionMatrix;

		bool m_ContentLoaded;

		std::shared_ptr<RenderEngine> mRenderEngine;
		std::shared_ptr<Camera> mCamera;

		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjMatrix();
	};
}