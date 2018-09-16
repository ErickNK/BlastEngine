#ifndef PHYSICS_ENGINE_INCLUDED_H
#define PHYSICS_ENGINE_INCLUDED_H


#include "PhysicsObject.h"
#include "Colliders/IntersectData.h"
#include "../Core/Entities/Entity.h"
#include <vector>

class PhysicsEngine {
public:
	PhysicsEngine() {}

	void AddObject(const PhysicsObject& object);

	void Simulate(float delta);

	void HandleCollisions();

private:
	std::vector<PhysicsObject> m_objects;
};

#endif