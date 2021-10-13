#pragma once
#include <Core/RenderEngine.hpp>
#include <directxmath.h>
// to be deleted
#include <d3dcompiler.h>


namespace APT {
	class PreviewRenderer {
	public:
		PreviewRenderer(const RenderEngine &renderEnigne);
		void Render();
	private:
		std::unique_ptr<DX::Resource> mVertexBuffer;
		std::unique_ptr<DX::Resource> mIndexBuffer;
		std::unique_ptr<DX::Resource> mDepthBuffer;

		D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;
		D3D12_INDEX_BUFFER_VIEW mIndexBufferView;

		std::unique_ptr<DX::DescriptorHeap> mDSVHeap;

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

	};
}