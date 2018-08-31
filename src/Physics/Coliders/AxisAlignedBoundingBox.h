#pragma once

#include "../../Core/math3d.h"
#include "IntersectData.h"

class AxisAlignedBoundingBox
{
public:
	AxisAlignedBoundingBox(const Vector3f& minExtents, const Vector3f& maxExtents) :
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

