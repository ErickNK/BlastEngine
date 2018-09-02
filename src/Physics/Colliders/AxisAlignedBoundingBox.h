#ifndef AXISALIGNEDBOUNDINGBOX_INCLUDED_H
#define AXISALIGNEDBOUNDINGBOX_INCLUDED_H

#include "../../Core/math3d.h"
#include "IntersectData.h"
#include "Collider.h"

class AxisAlignedBoundingBox: public Collider
{
public:
	AxisAlignedBoundingBox(const Vector3f& minExtents, const Vector3f& maxExtents) :
		Collider(Collider::TYPE_AABB),
		m_maxExtents(maxExtents),
		m_minExtents(minExtents) {};

	IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;

	inline const Vector3f GetMinExtents() const { return m_minExtents; }
	inline const Vector3f GetMaxExtents() const { return m_maxExtents; }

private:
	//This are two extreme corners of the box
	const Vector3f m_minExtents;
	const Vector3f m_maxExtents;
};

#endif