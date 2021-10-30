#pragma once
#include <PathTracer/Interaction/Interaction.hpp>
#include <PathTracer/Shape/Shape.hpp>
#include <PathTracer/Acceleration/Primitive.hpp>
namespace APT {
	class SurfaceInteraction : public Interaction {
	public:
		SurfaceInteraction(); 

		// Member
		Vec2f mUV;
		Vec3f mdPdU, mdPdV;
		Vec3f mdNdU, mdNdU;
		const Shape* shape = nullptr;
		struct {
			Vec3f mNormal;
			Vec3f mdPdU, mdPdV;
			Vec3f mdNdU, mdNdU;
		}mShading;

		const Primitive* primitive = nullptr;
	};
}