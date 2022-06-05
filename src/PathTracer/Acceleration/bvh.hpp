#pragma once
#include <PathTracer/Acceleration/Aggregate.hpp>
#include <memory>
#include <vector>

namespace APT {
	enum class BVHMethod {
		SAH,
		HLBVH,
		Middle,
		EqualCounts
	};

	struct BVHPrimitivesInfo
	{
		BVHPrimitivesInfo(size_t num, const Bounds3f& bounds) : num(num), bounds(bounds),
			centroid(.5f * bounds.pMin + .5f * bounds.pMax) { }
		size_t num;
		Bounds3f bounds;
		Vec3f centroid;
	};

	class BVH : public Aggregate {
	public:
		BVH(const std::vector<std::shared_ptr<Primitive>>& p, int maxPrimsInNode,
			BVHMethod method);
	private:
		const int mMaxPrimsInNode;
		const BVHMethod mMethod;
		std::vector<std::shared_ptr<Primitive>> mPrimitives;
	};
}