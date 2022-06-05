#pragma once
#include <PathTracer/Shape/Shape.hpp>
#include <PathTracer/Shape/TriangleMesh.hpp>
#include <PathTracer/Interaction/SurfaceInteraction.hpp>
namespace APT {
	class Triangle :public Shape {
	public:
		Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverse, const std::shared_ptr<TriangleMesh>& mesh, int num);

		Bounds3f ObjectBound() const;
		Bounds3f WorldBound() const;
		bool Intersect(const Ray& ray, float* tHit, SurfaceInteraction* isect,
			bool testAlphaTexture) const;
		bool IntersectP(const Ray& ray, bool testAlphaTexture) const;
		float Area() const;
		Interaction Sample(const Vec2f& u) const;
	private:
		void GetUVs(Vec2f uv[3]) const;

		std::shared_ptr<TriangleMesh> mMesh;
		const unsigned int* mIndex;
	};
}
