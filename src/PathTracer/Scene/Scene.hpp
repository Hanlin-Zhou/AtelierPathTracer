#pragma once
#include <PathTracer/Acceleration/SceneAggregate.hpp>

namespace APT {
	class Scene {
	public:
		Scene();

		std::shared_ptr<SceneAggregate> aggregate;
	};
}
