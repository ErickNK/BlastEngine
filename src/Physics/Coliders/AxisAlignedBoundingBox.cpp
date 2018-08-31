#include "AxisAlignedBoundingBox.h"


IntersectData AxisAlignedBoundingBox::IntersectAABB(const AxisAlignedBoundingBox & other) const
{
	/**
	* We try all extents and find the max. The wrongly facing extents will return
	* a negative.
	*/
	Vector3f distance1 = other.GetMinExtents() - m_maxExtents;
	Vector3f distance2 = m_minExtents - other.GetMaxExtents();
	Vector3f distances = Vector3f(distance1.Max(distance2));

	float maxDistance = distances.Max();

	return IntersectData(maxDistance < 0, maxDistance);
}
