#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <PathTracer/GeometryMath/Bounds.hpp>

namespace APT {
	class Ray;
	class SurfaceInteraction;

	class Shape {
	public:
		Shape(const Transform *objectToWorld);
		virtual Bounds3f ObjectBound() const = 0;
		virtual Bounds3f WorldBound() const = 0;
		virtual bool Intersect(const Ray& ray, float* tHit,
			SurfaceInteraction* isect,
			bool testAlphaTexture = true) const = 0;
		virtual bool IntersectP(const Ray& ray,
			bool testAlphaTexture = true) const {
			return Intersect(ray, nullptr, nullptr, testAlphaTexture);
		}
		// Members
		const Transform* mObjectToWorld;
	};
}