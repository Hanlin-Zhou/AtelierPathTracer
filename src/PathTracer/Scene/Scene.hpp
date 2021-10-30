#pragma once
#include <PathTracer/Acceleration/SceneAggregate.hpp>

namespace APT {
	class Scene {
	public:
		Scene();
		bool Intersect(const Ray& ray, SurfaceInteraction* isect) const;
		bool IntersectP(const Ray& ray) const;

		// Member
		std::shared_ptr<SceneAggregate> aggregate;
	};
}
