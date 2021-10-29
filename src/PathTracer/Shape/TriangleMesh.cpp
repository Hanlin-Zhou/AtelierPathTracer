#include "TriangleMesh.hpp"
namespace APT {
	TriangleMesh::TriangleMesh(const Transform& ObjectToWorld, int numTriangle, std::vector<unsigned int> vertexIndices, int numVertices, std::vector<Vec3f> vertexPoints,
		std::vector<Vec3f> tangent, std::vector<Vec3f> normal, std::vector<Vec2f> uv)
		:mNumTriangle(numTriangle), mNumVertice(numVertices)
	{
		mVertexIndices = vertexIndices;
		mVertex = vertexPoints;
		mTangent = tangent;
		mNormal = normal;
		mUV = uv;
	}
}