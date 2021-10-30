#pragma once
#include <PathTracer/GeometryMath/Vector.hpp>
#include <PathTracer/Media/Medium.hpp>
using namespace Math;

namespace APT {
	class Ray {
	public:
		Ray(const Vec3f& o, const Vec3f& d, float tMax = std::numeric_limits<float>::infinity(),
			float time = 0.f, const Medium* medium = nullptr);
		Vec3f operator()(float t) const;

		
		Vec3f o;
		Vec3f d;
		float mMaxTime;
		float mTime;
		const Medium* mMedium;
	};
}