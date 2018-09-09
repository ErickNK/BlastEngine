#ifndef PLANE_INCLUDED_H
#define PLANE_INCLUDED_H

#include "../../Common/math3d.h"
#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Collider.h"

class Plane : public Collider
{
public:
	Plane(const Vector3f& normal, const float distance) :
		Collider(Collider::TYPE_PLANE),
		m_normal(normal),
		m_distance(distance) {};

	Plane Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other) const;

	inline const Vector3f& GetNormal() const { return m_normal; }
	inline float GetDistance() const { return m_distance; }
private:
	const Vector3f m_normal;
	const float m_distance;
};

#endif