#include "Ray.hpp"
namespace APT {
	Ray::Ray(const Vec3f& o, const Vec3f& d, float tMax,
		float time, const Medium* medium) :
		o(o), d(d), mMaxTime(tMax), mTime(time), mMedium(medium) {}

	Vec3f Ray::operator()(float t) const
	{
		return o + d * t;
	}

}