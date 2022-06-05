#include "SurfaceInteraction.hpp"
namespace APT {
	SurfaceInteraction::SurfaceInteraction()
	{
	}
	SurfaceInteraction::SurfaceInteraction(const Vec3f& p, const Vec3f& pError, const Vec2f& uv, 
		const Vec3f& wo, const Vec3f& dpdu, const Vec3f& dpdv, const Vec3f& dndu, 
		const Vec3f& dndv, float time, const Shape* shape) :
		Interaction(p, Vec3f(Normalize(Cross(dpdu, dpdv))), pError, wo,
			time, nullptr),
		mUV(uv), mdPdU(dpdu), mdPdV(dpdv), mdNdU(dndu), mdNdV(dndv),
		mShape(shape)
	{
		mShading.mNormal = mNormal;
		mShading.mdPdU = mdPdU;
		mShading.mdPdV = mdPdV;
		mShading.mdNdU = mdNdU;
		mShading.mdNdV = mdNdV;
		if (mShape && (mShape->mReverseOrientation ^ shape->mSwapsHandedness)) {
			mNormal *= -1;
			mShading.mNormal *= -1;
		}
	}
	void SurfaceInteraction::SetShadingGeometry(const Vec3f& dpdus, const Vec3f& dpdvs, const Vec3f& dndus, const Vec3f& dndvs, bool orientationIsAuthoritative)
	{
		mShading.mNormal = Normalize((Vec3f)Cross(dpdus, dpdvs));
		if (mShape && (mShape->mReverseOrientation ^
			mShape->mSwapsHandedness))
			mShading.mNormal = -mShading.mNormal;
		if (orientationIsAuthoritative)
			mNormal = Faceforward(mNormal, mShading.mNormal);
		else
			mShading.mNormal = Faceforward(mShading.mNormal, mNormal);
		mShading.mdPdU = dpdus;
		mShading.mdPdV = dpdvs;
		mShading.mdNdU = dndus;
		mShading.mdNdV = dndvs;
	}
}