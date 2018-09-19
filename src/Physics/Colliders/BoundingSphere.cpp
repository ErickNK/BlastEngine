#include "Point.h"
#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "../Objects/PhysicsObject.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
	float radiusDistance = m_radius + other.m_radius;
	
	glm::vec3 directionToOther = (other.m_center - m_center);

	float centerDistance = glm::length(directionToOther);

	directionToOther / centerDistance; //Normalize

	float distanceApart = centerDistance - radiusDistance;

	return IntersectData(distanceApart < 0, directionToOther * distanceApart);	
}

void BoundingSphere::Transform(glm::vec3 translation)
{
	m_center += translation;
}

IntersectData BoundingSphere::IntersectAABB(const AxisAlignedBoundingBox &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData BoundingSphere::IntersectPlane(const Plane &other) const {
    return other.IntersectBoundingSphere(*this);
}

IntersectData BoundingSphere::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData BoundingSphere::IntersectPoint(const Point &point) const {
    glm::vec3 distanceToPoint = point.m_point - this->m_center;
    return {glm::length2(distanceToPoint) < (this->m_radius * this->m_radius) , distanceToPoint};
}

IntersectData BoundingSphere::Intersect(const Collider& other) const
{

    switch (other.GetType()){
        case TYPE_BOUNDINGSPHERE:{
            return this->IntersectBoundingSphere((BoundingSphere&)other);
        }
        case TYPE_AABB:{
            return this->IntersectAABB((AxisAlignedBoundingBox&)other);
        }
        case TYPE_PLANE:{
            return this->IntersectPlane((Plane&)other);
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
            return {false,glm::vec3()};
        }
    }
}

Point BoundingSphere::ClosestPoint(Point point) {

    // First, get a vetor from the sphere to the point
    glm::vec3 sphereToPoint = point.m_point - this->m_center;
    // Normalize that vector
    sphereToPoint = glm::normalize(sphereToPoint);
    // Adjust it's length to point to edge of sphere
    sphereToPoint *= this->m_radius;
    // Translate into world space
    glm::vec3 worldPoint = this->m_center + sphereToPoint;
    // Return new point
    return {worldPoint.x, worldPoint.y, worldPoint.z};
}


