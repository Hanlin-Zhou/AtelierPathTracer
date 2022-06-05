#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <vector>

namespace APT {
	class TriangleMesh {
	public:
		TriangleMesh(const Transform& ObjectToWorld, int numTriangle, const unsigned int* vertexIndices, int numVertices, const Vec3f* vertexPoints, const Vec3f* tangent, const Vec3f* normal, const Vec2f* uv);

		// Member 
		const int mNumTriangle;
		const int mNumVertice;

		std::vector<unsigned int> mVertexIndices;
		std::unique_ptr<Vec3f[]> mVertex;
		std::unique_ptr<Vec3f[]> mNormal;
		std::unique_ptr<Vec3f[]> mTangent;
		std::unique_ptr<Vec2f[]> mUV;
	};
}