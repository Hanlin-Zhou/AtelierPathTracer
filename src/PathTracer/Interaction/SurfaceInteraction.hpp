#pragma once
#include <PathTracer/Interaction/Interaction.hpp>
#include <PathTracer/Shape/Shape.hpp>
#include <PathTracer/Acceleration/Primitive.hpp>
namespace APT {
	class SurfaceInteraction : public Interaction {
	public:
		SurfaceInteraction(); 

		SurfaceInteraction(const Vec3f& p, const Vec3f& pError, const Vec2f& uv,
			const Vec3f& wo, const Vec3f& dpdu, const Vec3f& dpdv,
			const Vec3f& dndu, const Vec3f& dndv,
			float time, const Shape* sh);

		void SetShadingGeometry(const Vec3f& dpdus, const Vec3f& dpdvs, const Vec3f& dndus, const Vec3f& dndvs, bool orientationIsAuthoritative);
		// Member
		Vec2f mUV;
		Vec3f mdPdU, mdPdV;
		Vec3f mdNdU, mdNdV;
		const Shape* mShape = nullptr;
		struct {
			Vec3f mNormal;
			Vec3f mdPdU, mdPdV;
			Vec3f mdNdU, mdNdV;
		}mShading;

		//const Primitive* primitive = nullptr;
	};
}