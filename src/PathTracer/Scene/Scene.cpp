#include "Scene.hpp"
namespace APT {
    Scene::Scene()
    {
        aggregate = std::make_shared<SceneAggregate>();
    }
}