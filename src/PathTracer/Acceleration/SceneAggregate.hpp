#pragma once
#include <PathTracer/Acceleration/Primitive.hpp>
#include <PathTracer/Acceleration/Model.hpp>
#include <vector>

namespace APT {
	class SceneAggregate : public Primitive {
	public:
		SceneAggregate();

		std::vector<std::unique_ptr<Model>> mModels;
	private:

	};
}