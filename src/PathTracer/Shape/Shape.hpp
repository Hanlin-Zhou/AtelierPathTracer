#pragma once
#include <PathTracer/GeometryMath/Transform.hpp>
#include <PathTracer/GeometryMath/Bounds.hpp>

namespace APT {
	class Shape {
	public:
		Shape(const Transform *objectToWorld);

		virtual Bounds3f ObjectBound() const = 0;
		// Members
		const Transform* mObjectToWorld;
	};
}