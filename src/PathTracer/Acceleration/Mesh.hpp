#pragma once
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Shape/TriangleMesh.hpp>
#include <GraphicAPI/VertexBufferView.hpp>
#include <GraphicAPI/IndexBufferView.hpp>
#include <memory>
namespace APT {
	class Mesh : public Primitive {
	public:
		Mesh(const Transform& ObjectToWorld, int numTriangle, std::vector<unsigned int> vertexIndices, int numVertices,
			std::vector<Vec3f> vertexPoints, std::vector<Vec3f> tangent, std::vector<Vec3f> normal, std::vector<Vec2f> uv);


		std::unique_ptr<TriangleMesh> mMesh;
		std::unique_ptr<DX::VertexBufferView> mVertexView;
		std::unique_ptr<DX::VertexBufferView> mTangentView;
		std::unique_ptr<DX::VertexBufferView> mNormalView;
		std::unique_ptr<DX::VertexBufferView> mUVView;
		std::unique_ptr<DX::IndexBufferView> mIndexView;
	};
}