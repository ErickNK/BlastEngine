#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "Point.h"

template <class Parent> template <class OtherParent>
IntersectData BoundingSphere<Parent>::IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const
{
	float radiusDistance = m_radius + other.m_radius;
	
	Vector3f directionToOther = (other.m_center - m_center);

	float centerDistance = directionToOther.Length();

	directionToOther / centerDistance; //Normalize

	float distanceApart = centerDistance - radiusDistance;

	return IntersectData(distanceApart < 0, directionToOther * distanceApart);	
}

template <class Parent>
void BoundingSphere<Parent>::Transform(const Vector3f translation)
{
	m_center += translation;
}

template <class Parent> template <class OtherParent>
IntersectData BoundingSphere<Parent>::IntersectAABB(const AxisAlignedBoundingBox<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

template <class Parent> template <class OtherParent>
IntersectData BoundingSphere<Parent>::IntersectPlane(const Plane<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

template<class Parent>
IntersectData BoundingSphere<Parent>::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, Vector3f());
}

template <class Parent>
IntersectData BoundingSphere<Parent>::IntersectPoint(Point &point) const {
    Vector3f distanceToPoint = point.m_parent - this->m_center;
    return {distanceToPoint.LengthSq() < (this->m_radius * this->m_radius) , distanceToPoint};
}

template <class Parent> template <class OtherParent>
IntersectData BoundingSphere<Parent>::Intersect(const Collider<OtherParent>& other) const
{

    switch (other.m_type){
        case TYPE_BOUNDINGSPHERE:{
            return this->IntersectBoundingSphere((BoundingSphere<OtherParent>&)other);
        }
        case TYPE_AABB:{
            return this->IntersectAABB((AxisAlignedBoundingBox<OtherParent>&)other);
        }
        case TYPE_PLANE:{
            return this->IntersectPlane((Plane<OtherParent>&)other);
        }
        case TYPE_TERRAIN:{
            return this->IntersectTerrain((TerrainCollider&)other);
        }
        case TYPE_POINT:{
            return this->IntersectPoint((Point&)other);
        }
        case NUM_TYPES:break;
        default:{
            std::cerr << "Error: Collisions not implemented between specified colliders" << std::endl;
            return {false,0};
        }
    }
}

template<class Parent>
Point BoundingSphere<Parent>::ClosestPoint(Point point) {

    // First, get a vetor from the sphere to the point
    Vector3f sphereToPoint = point.m_parent - this->m_center;
    // Normalize that vector
    sphereToPoint = sphereToPoint.Normalized();
    // Adjust it's length to point to edge of sphere
    sphereToPoint *= this->m_radius;
    // Translate into world space
    Vector3f worldPoint = this->m_center + sphereToPoint;
    // Return new point
    return Point(worldPoint.GetX(), worldPoint.GetY(), worldPoint.GetZ());
}


