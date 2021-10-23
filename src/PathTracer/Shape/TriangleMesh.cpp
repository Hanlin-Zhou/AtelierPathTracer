#include "TriangleMesh.hpp"
namespace APT {
	TriangleMesh::TriangleMesh(const Transform& ObjectToWorld, int numTriangle, const int* vertexIndices, int numVertices, const int* vertexPoints, const int* tangent, const int* normal, const int* uv)
		:mNumTriangle(numTriangle), mNumVertice(numVertices), mVertexIndices(vertexIndices, vertexIndices + 3 * numTriangle)
	{
		if (tangent) {
			mTangent.reset(new Vec3f[mNumVertice]);
		}
		if (normal) {
			mNormal.reset(new Vec3f[mNumVertice]);
		}
		if (uv) {
			mUV.reset(new Vec3f[mNumVertice]);
		}
	}
}