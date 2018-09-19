#ifndef BOUNDINGSPHERE_INCLUDED_H
#define BOUNDINGSPHERE_INCLUDED_H

#include "../../Common/math3d.h"
#include "IntersectData.h"
#include "Collider.h"

class AxisAlignedBoundingBox;
class Plane;
class TerrainCollider;
class Point;

class BoundingSphere : public Collider
{
public:
	BoundingSphere() : Collider(TYPE_BOUNDINGSPHERE) {};

	BoundingSphere(const glm::vec3& center, float radius) :
		Collider(TYPE_BOUNDINGSPHERE),
		m_center(center),
		m_radius(radius) {};

	/**
	* Computes information about if this sphere intersects another collider.
	*
	* @param other The sphere that's being tested for intersection with this
	*                sphere.
	*/
	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

	IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;

	IntersectData IntersectPlane(const Plane& other) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    IntersectData IntersectPoint(const Point &point) const;

    IntersectData Intersect(const Collider& other) const override;

    Point ClosestPoint(Point point);

	/*
	* Move the sphere accordingly when a collision is detected.
	*
	*/
	void Transform(glm::vec3 translate) override;

	//GETTERS AND SETTERS
    glm::vec3 GetCenter() const override { return m_center; }
	inline float GetRadius() const { return m_radius; }
private:
	glm::vec3 m_center;
	float m_radius = 0;
};

#endif
