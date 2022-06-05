#include "bvh.hpp"

namespace APT {
	BVH::BVH(const std::vector<std::shared_ptr<Primitive>>& p, int maxPrimsInNode,
		BVHMethod method) : mMaxPrimsInNode(std::min(255, maxPrimsInNode)),
		mPrimitives(p), mMethod(method) 
	{
		std::vector<BVHPrimitivesInfo> pInfo(mPrimitives.size());
		for (size_t i = 0; i < mPrimitives.size(); i++)
		{
			pInfo[i] = { i, mPrimitives[i]->WorldBound()};
		}
	}
}
