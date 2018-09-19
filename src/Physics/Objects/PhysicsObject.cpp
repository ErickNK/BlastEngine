#include <cstring>
#include "PhysicsObject.h"

//template <class Entity> template <class OtherEntity>
//PhysicsObject<Entity>::PhysicsObject(const PhysicsObject<OtherEntity>& other) :
//	m_position(other.m_position),
//	m_oldPosition(other.m_oldPosition),
//	m_velocity(other.m_velocity),
//	m_collider(other.m_collider)
//{
//	m_collider->AddReference();
//}

//template <class Entity>
//PhysicsObject<Entity>::~PhysicsObject()
//{
//	if (m_collider->RemoveReference())
//	{
//		if (m_collider) delete m_collider;
//	}
//}
//
//void PhysicsObject::operator=(PhysicsObject other)
//{
//	//Implemented using the copy/swap idiom.
////	char* temp[sizeof(PhysicsObject) / sizeof(char)];
////	memcpy(temp, this, sizeof(PhysicsObject));
////	memcpy(this, &other, sizeof(PhysicsObject));
////	memcpy(&other, temp, sizeof(PhysicsObject));
//}