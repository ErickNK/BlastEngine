#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "Point.h"
#include <limits>

Plane::Plane(Point a, Point b, Point c) : Collider(TYPE_PLANE)
{
    m_normal = glm::normalize(glm::cross((b.m_point - a.m_point),( c.m_point - a.m_point)));
    m_distance = glm::dot(m_normal,a.m_point);
}

Plane Plane::Normalized() const
{
	float magnitude = glm::length(m_normal);

	return Plane(m_normal/magnitude, m_distance/magnitude);
}

IntersectData Plane::IntersectBoundingSphere(const BoundingSphere & other) const
{
	float distanceFromSphereCenter = fabs(glm::dot(m_normal,((other.GetCenter()) + m_distance)));
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0,m_normal * distanceFromSphere);
}

IntersectData Plane::IntersectAABB(const AxisAlignedBoundingBox& other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData Plane::IntersectPlane(const Plane &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData Plane::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData Plane::IntersectPoint(const Point &point) const {
    IntersectData result;
    float interaction = glm::dot(point.m_point,((m_normal) - m_distance));

    if (interaction == 0){
        result = IntersectData(true, glm::vec3());
        result.setInsideCollider(true);
        result.setBehindCollider(false);
    }else if(interaction < 0){ //behind
        result = IntersectData(false, glm::vec3());
        result.setInsideCollider(false);
        result.setBehindCollider(true);
    }else if(interaction > 0){ //in front
        result = IntersectData(false, glm::vec3());
        result.setInsideCollider(false);
        result.setBehindCollider(false);
    }

    return result;
}

Point Plane::ClosestPoint(Point &point) {
    // This works assuming plane.Normal is normalized, which it should be
    float distance = glm::dot(this->m_normal,((point.m_point) - this->m_distance));
    // If the plane normal wasn't normalized, we'd need this:
    // distance = distance / DOT(plane.Normal, plane.Normal);
    return point.m_point -  (m_normal * distance);
}

IntersectData Plane::Intersect(const Collider& other) const
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
        }case TYPE_POINT:{
            return this->IntersectPoint((Point&)other);
        }
        case NUM_TYPES:break;
        default:{
            std::cerr << "Error: Collisions not implemented between specified colliders" << std::endl;
            return {false,glm::vec3()};
        }
    }
}

Point Plane::IntersectAt(Plane p1, Plane p2, Plane p3) {
    Vector3f m1 = Vector3f(p1.m_normal.GetX(), p2.m_normal.GetX(), p3.m_normal.GetX());
    Vector3f m2 = Vector3f(p1.m_normal.GetY(), p2.m_normal.GetY(), p3.m_normal.GetY());
    Vector3f m3 = Vector3f(p1.m_normal.GetZ(), p2.m_normal.GetZ(), p3.m_normal.GetZ());
    Vector3f d = Vector3f(p1.Distance, p2.Distance, p3.Distance);
    Vector3f u = m2.Cross(m3);
    Vector3f v = m1.Cross(d);
    float denom = m1.Dot(u);

    if (fabs(denom) < std::numeric_limits<float>::epsilon()) {
        // Planes don't actually intersect in a point
        // Throw exception
        return Point(0, 0, 0);
    }

    return Point(
            d.Dot(u) / denom,
            m3.Dot(v) / denom,
            -m2.Dot(v) / denom
    );
}
