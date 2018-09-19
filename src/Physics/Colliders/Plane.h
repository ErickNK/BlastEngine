#ifndef PLANE_INCLUDED_H
#define PLANE_INCLUDED_H

#include "../../Common/math3d.h"
#include "BoundingSphere.h"
#include "IntersectData.h"

class Plane : public Collider
{
public:
	Plane():
		Collider(TYPE_PLANE),
		m_normal(glm::vec3(0,0,1)),
		m_distance(0){}

	Plane(const glm::vec3& normal, const float distance) :
		Collider(TYPE_PLANE),
		m_normal(normal),
		m_distance(distance) {};

	Plane(Point a, Point b, Point c);

	Plane Normalized() const;

	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

	IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;

	IntersectData IntersectPlane(const Plane& other) const;

	IntersectData IntersectTerrain(const TerrainCollider& other) const;

	IntersectData IntersectPoint(const Point& point) const;

	IntersectData Intersect(const Collider& other) const override;

	Point ClosestPoint(Point& point);

	Point IntersectAt(Plane a, Plane b, Plane c);

	inline const glm::vec3& GetNormal() const { return m_normal; }
	inline float GetDistance() const { return m_distance; }

private:
	/**
	 * Normal from plane
	 * */
	const glm::vec3 m_normal;
	/**
	 * Distance from origin in world space
	 * */
	const float m_distance;
};
#endif