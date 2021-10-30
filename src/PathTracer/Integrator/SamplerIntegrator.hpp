#pragma once
#include <PathTracer/Integrator/Integrator.hpp>
#include <PathTracer/Camera/Camera.hpp>

namespace APT {
	class SamplerIntegrator : public Integrator {
	public:

	protected:
		std::shared_ptr<const Camera> camera;

	};
}