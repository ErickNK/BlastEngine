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
    float m = (end.m_point.y - start.m_point.y)
            / (end.m_point.x - start.m_point.x);
    float b = start.m_point.y - m * start.m_point.x;
// At this point, evaluating the equation should be:
// return point.y == m * point.x + b;
// But that won't work, because we're working with floats
// floating point error can accumulate, we have to use an epsilon
// using an epislon, we can compare the distance of the
// equations result to 0 by the epsilon
    if (fabs(point.m_point.y - (m * point.m_point.x + b)) < std::numeric_limits<float>::epsilon()) {
        return IntersectData(true, glm::vec3());;
    }
    return IntersectData(false, glm::vec3());
// EPSILON is just a small number, like 0.001f;
}


IntersectData Line::Intersect(const Collider& other) const
{

    switch (other.GetType()){
//        case TYPE_BOUNDINGSPHERE:{
//            return this->IntersectBoundingSphere((BoundingSphere&)other);
//        }
//        case TYPE_AABB:{
//            return this->IntersectAABB((AxisAlignedBoundingBox&)other);
//        }
//        case TYPE_PLANE:{
//            return this->IntersectPlane((Plane&)other);
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
            return {false,glm::vec3()};
        }
    }
}
