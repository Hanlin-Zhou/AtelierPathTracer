#pragma once
#include <PathTracer/Ray/Ray.hpp>
#include <PathTracer/Interaction/SurfaceInteraction.hpp>

namespace APT {
	//abstract class
	class Primitive {
	public:
		virtual Bounds3f WorldBound() const = 0;
		
		//return 
		virtual bool Intersect(const Ray& r, SurfaceInteraction*) const = 0;
		virtual bool IntersectP(const Ray& r) const = 0;
		/*virtual const AreaLight* GetAreaLight() const = 0;
		virtual const Material* GetMaterial() const = 0;
		virtual void ComputeScatteringFunctions(SurfaceInteraction* isect,
			MemoryArena& arena, TransportMode mode,
			bool allowMultipleLobes) const = 0;*/
	};
}