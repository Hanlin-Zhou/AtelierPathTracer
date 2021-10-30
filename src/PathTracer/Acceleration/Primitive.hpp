#pragma once
#include <PathTracer/Ray/Ray.hpp>
#include <PathTracer/Interaction/SurfaceInteraction.hpp>
namespace APT {
	class Primitive {
	public:
		virtual Bounds3f WorldBound() const = 0;
		virtual bool Intersect(const Ray& r, SurfaceInteraction*) const = 0;
		virtual bool IntersectP(const Ray& r) const = 0;
	};
}