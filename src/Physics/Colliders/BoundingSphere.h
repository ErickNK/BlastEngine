#ifndef BOUNDINGSPHERE_INCLUDED_H
#define BOUNDINGSPHERE_INCLUDED_H

#include "../../Common/math3d.h"
#include "IntersectData.h"
#include "Collider.h"

template <class Parent> class AxisAlignedBoundingBox;
template <class Parent> class Plane;
class TerrainCollider;
class Point;

template <class Parent>
class BoundingSphere : public Collider<Parent>
{
public:
	BoundingSphere(const Vector3f& center, float radius) :
		Collider<Parent>(TYPE_BOUNDINGSPHERE),
		m_center(center),
		m_radius(radius) {};

	/**
	* Computes information about if this sphere intersects another collider.
	*
	* @param other The sphere that's being tested for intersection with this
	*                sphere.
	*/
    template <class OtherParent>
	IntersectData IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const;

    template <class OtherParent>
	IntersectData IntersectAABB(const AxisAlignedBoundingBox<OtherParent>& other) const;

    template <class OtherParent>
	IntersectData IntersectPlane(const Plane<OtherParent>& other) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    IntersectData IntersectPoint(Point &point) const;

    template <class OtherParent>
    IntersectData Intersect(const Collider<OtherParent>& other) const;

    Point ClosestPoint(Point point);

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
