#pragma once
#include <PathTracer/Ray/Ray.hpp>

namespace APT {
	class RayDifferential : public Ray {
	public:
		RayDifferential(const Vec3f& o, const Vec3f& d, float tMax,
			float time = 0.f, const Medium* medium = nullptr);
		RayDifferential(const Ray& ray);
		void ScaleDifferentials(float s);

		// Members
		bool mHasDiff = false;
		Vec3f mRxOrigin, mRyOrigin;
		Vec3f mRxDirection, mRyDirection;
	};
}