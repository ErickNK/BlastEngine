//
// Created by erick on 9/16/18.
//

#include "Line.h"
#include "Point.h"
#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include <limits>

IntersectData Line::IntersectPoint(Point &point) const {
    float m = (this->m_parent.second.GetParent().GetY() - this->m_parent.first.GetParent().GetY())
            / (this->m_parent.second.GetParent().GetX() - this->m_parent.first.GetParent().GetX());
    float b = this->m_parent.first.GetParent().GetY() - m * this->m_parent.first.GetParent().GetX();
// At this point, evaluating the equation should be:
// return point.y == m * point.x + b;
// But that won't work, because we're working with floats
// floating point error can accumulate, we have to use an epsilon
// using an epislon, we can compare the distance of the
// equations result to 0 by the epsilon
    if (fabs(point.GetParent().GetY() - (m * point.GetParent().GetX() + b)) < std::numeric_limits<float>::epsilon()) {
        return IntersectData(true, Vector3f());;
    }
    return IntersectData(false, Vector3f());
// EPSILON is just a small number, like 0.001f;
}


template <class OtherParent>
IntersectData Line::Intersect(const Collider<OtherParent>& other) const
{

    switch (other.m_type){
//        case TYPE_BOUNDINGSPHERE:{
//            return this->IntersectBoundingSphere((BoundingSphere<OtherParent>&)other);
//        }
//        case TYPE_AABB:{
//            return this->IntersectAABB((AxisAlignedBoundingBox<OtherParent>&)other);
//        }
//        case TYPE_PLANE:{
//            return this->IntersectPlane((Plane<OtherParent>&)other);
//        }
//        case TYPE_TERRAIN:{
//            return this->IntersectTerrain((TerrainCollider&)other);
//        }
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
