#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <vector>

namespace APT {
	class TriangleMesh {
	public:
		TriangleMesh(const Transform& ObjectToWorld, int numTriangle, const int* vertexIndices, int numVertices, const int* vertexPoints, const int* tangent, const int* normal, const int* uv);

		// Member 
		const int mNumTriangle;
		const int mNumVertice;

		
		std::vector<int> mVertexIndices;
		std::unique_ptr<Vec3f[]> mVertex;
		std::unique_ptr<Vec3f[]> mNormal;
		std::unique_ptr<Vec3f[]> mTangent;
		std::unique_ptr<Vec3f[]> mUV;

	};
}