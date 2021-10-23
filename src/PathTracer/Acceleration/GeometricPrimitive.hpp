#pragma once
#include <memory>
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Shape/Shape.hpp>

namespace APT {
	class GeometricPrimitive : public Primitive {
	public:
		GeometricPrimitive();
		

		// Member
		std::shared_ptr<Shape> mShape;
	};
}