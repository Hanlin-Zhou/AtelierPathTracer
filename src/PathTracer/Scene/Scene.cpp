#include "Scene.hpp"
namespace APT {
    Scene::Scene()
    {
        aggregate = std::make_shared<SceneAggregate>();
    }

    bool Scene::Intersect(const Ray& ray, SurfaceInteraction* isect) const {
        //return aggregate->Intersect(ray, isect);
        return false;
    }

    bool Scene::IntersectP(const Ray& ray) const {
        //return aggregate->IntersectP(ray);
        return false;
    }

}