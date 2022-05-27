#pragma once
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Acceleration/Model.hpp>
#include <vector>

namespace APT {
	class SceneAggregate : public Primitive {
	public:
		SceneAggregate();

		/*virtual Bounds3f WorldBound() const;
		virtual bool Intersect(const Ray& r, SurfaceInteraction*) const;
		virtual bool IntersectP(const Ray& r) const;*/

		std::vector<std::unique_ptr<Model>> mModels;
	private:

	};
}