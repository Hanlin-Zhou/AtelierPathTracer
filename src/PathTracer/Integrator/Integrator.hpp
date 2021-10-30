#pragma once
#include <PathTracer/Scene/Scene.hpp>

namespace APT {
	class Integrator {
		virtual void Render(const Scene& scene) = 0;
	};
}