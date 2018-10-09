#ifndef PHYSICS_ENGINE_INCLUDED_H
#define PHYSICS_ENGINE_INCLUDED_H


#include "Objects/PhysicsObject.h"
#include "Colliders/IntersectData.h"
#include "../Core/Entities/Entity.h"
#include "Objects/RigidBody.h"
#include "../Core/Scene.h"
#include <vector>

class PhysicsEngine {
public:
	PhysicsEngine() = default;

    void Initialize();

	void Simulate(double time, float delta, Scene* scene);

	void HandleCollisions(Scene* scene);
};

#endif