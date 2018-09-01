#include "BoundingSphere.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other) const
{
	float radiusDistance = m_radius + other.m_radius;
	
	Vector3f directionToOther = (other.m_center - m_center);

	float centerDistance = directionToOther.Length();

	directionToOther / centerDistance; //Normalize

	float distanceApart = centerDistance - radiusDistance;

	return IntersectData(distanceApart < 0, directionToOther * distanceApart);	
}

void BoundingSphere::Transform(const Vector3f translation)
{
	m_center += translation;
}
