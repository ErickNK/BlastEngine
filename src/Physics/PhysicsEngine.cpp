#include "PhysicsEngine.h"

void PhysicsEngine::AddObject(const PhysicsObject& object)
{
	m_objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta)
{
	for (unsigned int i = 0; i < m_objects.size(); i++) {
		m_objects[i].Integrate(delta);
	}
}

void PhysicsEngine::HandleCollisions()
{
	//Iterate checking for collision between every object in the engine
	for (unsigned int i = 0; i < m_objects.size(); i++) {

		for (unsigned int j = i + 1 /*Not checking the upper loop with itself*/; 
			j < m_objects.size(); j++) {
			//Check if intersecting
			IntersectData intersectData = m_objects[i].GetCollider().Intersect(m_objects[j].GetCollider());

			if (intersectData.GetDoesIntersect()) {
				//React to collision.

				//Reflect against the collision direction
				Vector3f direction = intersectData.GetDirection().Normalized();
				Vector3f otherDirection = Vector3f(direction.Reflect(m_objects[i].GetVelocity().Normalized()));

				m_objects[i].SetVelocity(
					Vector3f(m_objects[i].GetVelocity().Reflect(otherDirection))
					);
				m_objects[j].SetVelocity(
					Vector3f(m_objects[j].GetVelocity().Reflect(direction)) //Reflect in the other direction
				);
			}
		}

	}
}