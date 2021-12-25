#pragma once
#include <PathTracer/GeometryMath/Vector.hpp>
using namespace Math;

namespace APT {
    struct CameraSample {
        Vec2f mFilm;
        Vec2f mLens;
        float mTime;
    };
}