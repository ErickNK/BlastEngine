
#ifndef COLLIDER_INCLUDED_H
#define COLLIDER_INCLUDED_H

#include <iostream>
#include "IntersectData.h"
#include "../../Common/math3d.h"
#include "../../Common/referenceCounter.h"
#include "../../Common/CommonValues.h"
#include "../../Core/Entities/Entity.h"

class PhysicsObject;

class Collider: public ReferenceCounter {
public:
	explicit Collider(ColliderType type) :
		ReferenceCounter(),
		m_type(type) {}

	virtual IntersectData Intersect(const Collider& other) const {};
	virtual void Update(){}

	inline ColliderType GetType() const { return m_type;}
    inline void SetType(ColliderType type){ m_type = type;}
	inline PhysicsObject* GetParent() const { return m_parent;}
	inline void SetParent(PhysicsObject* parent){ m_parent = parent;}

protected:
	ColliderType m_type;
    PhysicsObject* m_parent{};
};
#endif