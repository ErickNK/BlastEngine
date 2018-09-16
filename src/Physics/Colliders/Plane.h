#ifndef PLANE_INCLUDED_H
#define PLANE_INCLUDED_H

#include "../../Common/math3d.h"
#include "BoundingSphere.h"
#include "IntersectData.h"

template <class Parent>
class Plane : public Collider<Parent>
{
public:
	Plane():
		Collider<Parent>(TYPE_PLANE),
		m_normal(Vector3f(0,0,1)),
		m_distance(0){}

	Plane(const Vector3f& normal, const float distance) :
		Collider<Parent>(TYPE_PLANE),
		m_normal(normal),
		m_distance(distance) {};

	Plane(Point a, Point b, Point c);

	Plane Normalized() const;

	template <class OtherParent>
	IntersectData IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const;

	template <class OtherParent>
	IntersectData IntersectAABB(const AxisAlignedBoundingBox<OtherParent>& other) const;

	template <class OtherParent>
	IntersectData IntersectPlane(const Plane<OtherParent>& other) const;

	IntersectData IntersectTerrain(const TerrainCollider& other) const;

	IntersectData IntersectPoint(const Point& point) const;

	template <class OtherParent>
	IntersectData Intersect(const Collider<OtherParent>& other) const;

	Point ClosestPoint(Point& point);

	Point IntersectAt(Plane a, Plane b, Plane c);

	inline const Vector3f& GetNormal() const { return m_normal; }
	inline float GetDistance() const { return m_distance; }

private:
	/**
	 * Normal from plane
	 * */
	const Vector3f m_normal;
	/**
	 * Distance from origin in world space
	 * */
	const float m_distance;
};
#endif