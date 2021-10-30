#pragma once
#include <PathTracer/GeometryMath/Vector.hpp>
#include <PathTracer/Media/Medium.hpp>
using namespace Math;
namespace APT {
	class Interaction {
	public:
		Interaction();

		// Members:
		Vec3f p;
		float mTime;
		Vec3f mWo;
		Vec3f mError;



	};
}