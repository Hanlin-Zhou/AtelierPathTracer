#include "RNG.hpp"
namespace APT {
    RNG::RNG()
    {
    }
    RNG::RNG(unsigned long sequence)
    {
    }
    void RNG::SetSequence(unsigned long sequence)
    {
    }
    unsigned int RNG::UniformUInt32()
    {
        return 0;
    }
    unsigned int RNG::UniformUInt32(unsigned int b)
	{
        unsigned int threshold = (~b + 1u) % b;
        while (true) {
            unsigned int r = UniformUInt32();
            if (r >= threshold)
                return r % b;
        }
	}
    float RNG::UniformFloat()
    {
        return 0.0f;
    }
}