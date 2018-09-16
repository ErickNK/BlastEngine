
#ifndef COLLIDER_INCLUDED_H
#define COLLIDER_INCLUDED_H

#include <iostream>
#include "IntersectData.h"
#include "../../Common/math3d.h"
#include "../../Common/referenceCounter.h"
#include "../../Common/CommonValues.h"

template <class Parent>
class Collider: public ReferenceCounter {
public:
	Collider(ColliderType type) :
		ReferenceCounter(),
		m_type(type) {}

	virtual IntersectData Intersect(const Collider& other) const {};
	virtual void Transform(const Vector3f translation) {};

	inline ColliderType GetType() const { return m_type;}
    inline void SetType(ColliderType type){ m_type = type;}
    inline void SetParent(Parent parent){ m_parent = parent;}
    inline Parent GetParent() const { return m_parent;}

	virtual Vector3f GetCenter() const { return Vector3f(0,0,0); }

protected:
	ColliderType m_type;
	Parent m_parent;
};
#endif