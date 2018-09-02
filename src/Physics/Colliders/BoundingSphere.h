#ifndef BOUNDINGSPHERE_INCLUDED_H
#define BOUNDINGSPHERE_INCLUDED_H

#include "../../Core/math3d.h"
#include "IntersectData.h"
#include "Collider.h"

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const Vector3f& center, float radius) :
		Collider(Collider::TYPE_BOUNDINGSPHERE),
		m_center(center),
		m_radius(radius) {};

	/**
	* Computes information about if this sphere intersects another aphere.
	*
	* @param other The sphere that's being tested for intersection with this
	*                sphere.
	*/
	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

	/*
	* Move the sphere accordingly when a collision is detected.
	*
	*/
	virtual void Transform(const Vector3f translate);

	//GETTERS AND SETTERS
	virtual Vector3f GetCenter() const { return m_center; }
	inline float GetRadius() const { return m_radius; }
private:
	Vector3f m_center;
	float m_radius;
};

#endif
