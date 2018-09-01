
#ifndef COLLIDER_INCLUDED_H
#define COLLIDER_OBJECT_INCLUDED_H

#include <iostream>
#include "IntersectData.h"
#include "../../Core/math3d.h"
#include "../../Core/referenceCounter.h"
#include "BoundingSphere.h"

class Collider: public ReferenceCounter {
public:
	Collider(int type) :
		ReferenceCounter(),
		m_type(type) {}
	
	enum {
		TYPE_BOUNDINGSPHERE,
		TYPE_AABB,

		NUM_TYPES
	};

	IntersectData Intersect(const Collider& other) const;

	virtual void Transform(const Vector3f translation) {};

	inline int GetType() const { return m_type; }
	virtual Vector3f GetCenter() const { return Vector3f(0,0,0); }

private:
	int m_type;
};
#endif