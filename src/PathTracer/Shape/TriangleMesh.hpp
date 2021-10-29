#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <vector>

namespace APT {
	class TriangleMesh {
	public:
		TriangleMesh(const Transform& ObjectToWorld, int numTriangle, std::vector<unsigned int> vertexIndices, int numVertices, std::vector<Vec3f> vertexPoints, std::vector<Vec3f> tangent, std::vector<Vec3f> normal, std::vector<Vec2f> uv);

		// Member 
		const int mNumTriangle;
		const int mNumVertice;

		
		std::vector<unsigned int> mVertexIndices;
		std::vector<Vec3f> mVertex;
		std::vector<Vec3f> mNormal;
		std::vector<Vec3f> mTangent;
		std::vector<Vec2f> mUV;

	};
}