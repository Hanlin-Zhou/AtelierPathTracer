#pragma once
#include <cstdlib>

namespace APT {
	class RNG {
	public:
		RNG();
		RNG(unsigned long sequence);

		void SetSequence(unsigned long sequence);
		unsigned int UniformUInt32();
		unsigned int UniformUInt32(unsigned int b);

	private:

	};
}