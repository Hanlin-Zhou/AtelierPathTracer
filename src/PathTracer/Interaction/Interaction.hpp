#pragma once
#include <PathTracer/GeometryMath/Vector.hpp>
#include <PathTracer/Media/Medium.hpp>
using namespace Math;
namespace APT {
	class Interaction {
	public:
		Interaction();
		Interaction(const Vec3f& p, const Vec3f& n, const Vec3f& pError,
			const Vec3f& wo, float time, const MediumInterface* mediumInterface
			);
		// Members:
		Vec3f mP;
		float mTime;
		Vec3f mWo;
		Vec3f mError;
		Vec3f mNormal;
		MediumInterface mMediumInterface;



	};
}