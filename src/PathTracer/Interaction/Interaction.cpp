#include "Interaction.hpp"
namespace APT {
	Interaction::Interaction() : mTime(0) {}

	Interaction::Interaction(const Vec3f& p, const Vec3f& n, const Vec3f& pError,
		const Vec3f& wo, float time, const MediumInterface* mediumInterface
	): mP(p), mTime(time), mError(pError), mWo(wo), mNormal(n), mMediumInterface(*mediumInterface)
	{}


}