#include "TriangleMesh.hpp"
namespace APT {
	TriangleMesh::TriangleMesh(const Transform& ObjectToWorld, int numTriangle, const unsigned int* vertexIndices,
		int numVertices, const Vec3f* vertexPoints, const Vec3f* tangent, const Vec3f* normal, const Vec2f* uv)
		:mNumTriangle(numTriangle), mNumVertice(numVertices), mVertexIndices(vertexIndices, vertexIndices + 3 * numVertices)
	{
		mVertex.reset(new Vec3f[mNumVertice]);
		for (int i = 0; i < mNumVertice; ++i)
			mVertex[i] = ObjectToWorld.TransformPoint(vertexPoints[i]);

		if (uv) {
			mUV.reset(new Vec2f[mNumVertice]);
			memcpy(mUV.get(), uv, mNumVertice * sizeof(Vec2f));
		}

		if (normal) {
			mNormal.reset(new Vec3f[mNumVertice]);
			for (int i = 0; i < mNumVertice; ++i)
				mNormal[i] = ObjectToWorld.TransformNormal(normal[i]);
		}
		if (tangent) {
			mTangent.reset(new Vec3f[mNumVertice]);
			for (int i = 0; i < mNumVertice; ++i)
				mTangent[i] = ObjectToWorld.TransformVector(tangent[i]);
		}
	}
}