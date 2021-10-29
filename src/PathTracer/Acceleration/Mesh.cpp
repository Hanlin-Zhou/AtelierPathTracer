#include "Mesh.hpp"
namespace APT {
	Mesh::Mesh(const Transform& ObjectToWorld, int numTriangle, std::vector<unsigned int> vertexIndices, int numVertices,
		std::vector<Vec3f> vertexPoints, std::vector<Vec3f> tangent, std::vector<Vec3f> normal, std::vector<Vec2f> uv)
	{
		mMesh = std::make_unique<TriangleMesh>(ObjectToWorld, numTriangle, vertexIndices, numVertices, vertexPoints, tangent, normal, uv);
	}
}