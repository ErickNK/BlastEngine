#ifndef AXISALIGNEDBOUNDINGBOX_INCLUDED_H
#define AXISALIGNEDBOUNDINGBOX_INCLUDED_H

#include "../../Common/math3d.h"
#include "IntersectData.h"
#include "Collider.h"
#include "Point.h"

template <class Parent> class BoundingSphere;
template <class Parent> class Plane;
class TerrainCollider;

template <class Parent>
class AxisAlignedBoundingBox: public Collider<Parent>
{
public:
	AxisAlignedBoundingBox(const Vector3f& minExtents, const Vector3f& maxExtents) :
		Collider<Parent>(Collider<Parent>::TYPE_AABB),
		m_maxExtents(maxExtents),
		m_minExtents(minExtents)
    {
	    if(!IsValid()){
	        Fix();
	    }
	    //TODO: figure out center and extents
	}

    AxisAlignedBoundingBox(const Point& center, const Vector3f& extents) :
            Collider<Parent>(Collider<Parent>::TYPE_AABB),
            m_center(center),
            m_extents_vec(extents) {}

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

    bool IsValid();
    void Fix();

	inline const Vector3f GetMinExtents() const { return m_minExtents; }
	inline const Vector3f GetMaxExtents() const { return m_maxExtents; }

private:
	//This are two extreme corners of the box
	const Vector3f m_minExtents;
	const Vector3f m_maxExtents;
	const Point m_center;
	const Vector3f m_extents_vec;
};

#endif