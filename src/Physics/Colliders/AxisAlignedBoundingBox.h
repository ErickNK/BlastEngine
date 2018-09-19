#include <utility>

#ifndef AXISALIGNEDBOUNDINGBOX_INCLUDED_H
#define AXISALIGNEDBOUNDINGBOX_INCLUDED_H

#include "../../Common/math3d.h"
#include "IntersectData.h"
#include "Collider.h"
#include "Point.h"

class BoundingSphere;
class Plane;
class TerrainCollider;

class AxisAlignedBoundingBox: public Collider
{
public:
	AxisAlignedBoundingBox(const glm::vec3& minExtents, const glm::vec3& maxExtents) :
		Collider(TYPE_AABB),
		m_maxExtents(maxExtents),
		m_minExtents(minExtents)
    {
	    if(!IsValid()){
	        Fix();
	    }
	    //TODO: figure out center and extents
	}

    AxisAlignedBoundingBox(Point center, const glm::vec3& extents) :
            Collider(TYPE_AABB),
            m_center(std::move(center)),
            m_extents_vec(extents) {}

    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;
    IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;
    IntersectData IntersectPlane(const Plane& other) const;
    IntersectData IntersectTerrain(const TerrainCollider& other) const;
    IntersectData IntersectPoint(const Point& point) const;
    IntersectData Intersect(const Collider& other) const;

    Point ClosestPoint(Point& point);

    bool IsValid();
    void Fix();

	inline const Point GetMinExtents() const { return m_minExtents; }
	inline const Point GetMaxExtents() const { return m_maxExtents; }

private:
	//This are two extreme corners of the box
	Point m_minExtents;
	Point m_maxExtents;
	Point m_center;
	glm::vec3 m_extents_vec;
};

#endif