#include "PhysicsEngine.h"

void PhysicsEngine::Initialize() {

}

void PhysicsEngine::Simulate(double time, float delta, Scene* scene)
{
	for (auto &i : scene->getPhysicsObjects()) {
		i->Integrate(time, delta);
	}
}

void PhysicsEngine::HandleCollisions(Scene* scene)
{
	//Iterate checking for collision between every object in the engine
	for (unsigned int i = 0; i < scene->getPhysicsObjects().size(); i++) {

		for (unsigned int j = i + 1 /*Not checking the upper loop with itself*/; 
			j < scene->getPhysicsObjects().size(); j++) {
			//Check if intersecting
			IntersectData intersectData = scene->getPhysicsObjects()[i]->getCollider()->Intersect(*scene->getPhysicsObjects()[j]->getCollider());

			if (intersectData.GetDoesIntersect()) {
				//React to collision.

				scene->getPhysicsObjects()[i]->React(scene->getPhysicsObjects()[j],intersectData);
				scene->getPhysicsObjects()[j]->React(scene->getPhysicsObjects()[i],intersectData.inverse());
				//Reflect against the collision direction
//				Vector3f direction = intersectData.GetDirection().Normalized();
//				Vector3f otherDirection = Vector3f(direction.Reflect(m_objects[i].GetVelocity().Normalized()));
//
//				m_objects[i].SetVelocity(
//					Vector3f(m_objects[i].GetVelocity().Reflect(otherDirection))
//					);
//				m_objects[j].SetVelocity(
//					Vector3f(m_objects[j].GetVelocity().Reflect(direction)) //Reflect in the other direction
//				);
			}
		}

	}
}