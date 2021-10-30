#include "RayDifferential.hpp"
namespace APT {
	RayDifferential::RayDifferential(const Vec3f& o, const Vec3f& d, float tMax, float time, const Medium* medium):
		Ray(o, d, tMax, time, medium)
	{
		mHasDiff = false;
	}
	RayDifferential::RayDifferential(const Ray& ray):
		Ray(ray)
	{
		mHasDiff = false;
	}
	void RayDifferential::ScaleDifferentials(float s)
	{
		mRxOrigin = o + (mRxOrigin - o) * s;
		mRyOrigin = o + (mRyOrigin - o) * s;
		mRxDirection = d + (mRxDirection - d) * s;
		mRyDirection = d + (mRyDirection - d) * s;
	}
}