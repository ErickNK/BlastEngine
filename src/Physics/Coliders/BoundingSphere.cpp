#include "BoundingSphere.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
{
	float radiusDistance = m_radius + other.m_radius;
	float centerDistance = (other.m_center - m_center).Length();

	if (centerDistance < radiusDistance) { //Intersecting
		return IntersectData(true, centerDistance - radiusDistance); 
	}
	else //Not intersecting
	{
		return IntersectData(false, centerDistance - radiusDistance);
	}
}
