#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <PathTracer/GeometryMath/Bounds.hpp>
#include <PathTracer/Interaction/Interaction.hpp>

namespace APT {
	class Ray;
	class SurfaceInteraction;

	class Shape {
	public:
		Shape(const Transform *objectToWorld, const Transform *worldToObject,
			bool reverseOrientation);
		virtual ~Shape();
		virtual Bounds3f ObjectBound() const = 0;
		virtual Bounds3f WorldBound() const;

		// return first ray-shape interaction
		virtual bool Intersect(const Ray& ray, float* tHit,
			SurfaceInteraction* isect,
			bool testAlphaTexture = true) const = 0;

		// intersect but does not required interaction data, just boolean
		virtual bool IntersectP(const Ray& ray,
			bool testAlphaTexture = true) const {
			return Intersect(ray, nullptr, nullptr, testAlphaTexture);
		}

		virtual float Area() const = 0;

		virtual float Pdf(const Interaction&) const {
			return 1 / Area();
		}

		virtual Interaction Sample(const Vec2f& u) const;

		virtual Interaction Sample(const Interaction& ref,
			const Vec2f& u) const {
			return Sample(u);
		}

		virtual float Pdf(const Interaction& ref, const Vec3f& wi) const;
		// Members

		const Transform* mObjectToWorld;
		const Transform* mWorldToObject;
		const bool mReverseOrientation;
		const bool mSwapsHandedness;
	};
}