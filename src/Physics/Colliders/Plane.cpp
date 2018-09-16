#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "Point.h"
#include <limits>

template<class Parent>
Plane<Parent>::Plane(Point a, Point b, Point c) : Collider<Parent>(Collider<Parent>::TYPE_PLANE)
{
    m_normal = ((b.m_parent - a.m_parent).Cross( c.m_parent - a.m_parent)).Normalized();
    m_distance = m_normal.Dot(a.m_parent);
}

template <class Parent>
Plane<Parent> Plane<Parent>::Normalized() const
{
	float magnitude = m_normal.Length();

	return Plane(m_normal/magnitude, m_distance/magnitude);
}

template <class Parent> template <class OtherParent>
IntersectData Plane<Parent>::IntersectBoundingSphere(const BoundingSphere<OtherParent> & other) const
{
	float distanceFromSphereCenter = fabs(m_normal.Dot(other.GetCenter()) + m_distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0,m_normal * distanceFromSphere);
}

template <class Parent> template <class OtherParent>
IntersectData Plane<Parent>::IntersectAABB(const AxisAlignedBoundingBox<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

template <class Parent> template <class OtherParent>
IntersectData Plane<Parent>::IntersectPlane(const Plane<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

template<class Parent>
IntersectData Plane<Parent>::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, Vector3f());
}


template<class Parent>
IntersectData Plane<Parent>::IntersectPoint(const Point &point) const {
    IntersectData result;
    float interaction = (point.m_parent.Dot(m_normal) - m_distance);

    if (interaction == 0){
        result = IntersectData(true, Vector3f());
        result.setInsideCollider(true);
        result.setBehindCollider(false);
    }else if(interaction < 0){ //behind
        result = IntersectData(false, Vector3f());
        result.setInsideCollider(false);
        result.setBehindCollider(true);
    }else if(interaction > 0){ //in front
        result = IntersectData(false, Vector3f());
        result.setInsideCollider(false);
        result.setBehindCollider(false);
    }

    return result;
}

template<class Parent>
Point Plane<Parent>::ClosestPoint(Point &point) {
    // This works assuming plane.Normal is normalized, which it should be
    float distance = this->m_normal.Dot(point.m_parent) - this->m_distance;
    // If the plane normal wasn't normalized, we'd need this:
    // distance = distance / DOT(plane.Normal, plane.Normal);
    return point.m_parent -  (m_normal * distance);
}

template <class Parent> template <class OtherParent>
IntersectData Plane<Parent>::Intersect(const Collider<OtherParent>& other) const
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
        }case TYPE_POINT:{
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
Point Plane<Parent>::IntersectAt(Plane p1, Plane p2, Plane p3) {
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
