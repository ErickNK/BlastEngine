//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINT_H

#include <glm/glm.hpp>
#include "Collider.h"


class AxisAlignedBoundingBox;
class BoundingSphere;
class Plane;
class TerrainCollider;

class Point : public Collider{
public:
    Point(): Collider(TYPE_POINT){};

    Point(float x, float y, float z): Collider(TYPE_POINT){
        m_point = glm::vec3(x,y,z);
    }

    Point(glm::vec3 vec): Collider(TYPE_POINT){
        m_point = vec;
    }

    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

    IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;

    IntersectData IntersectPlane(const Plane &other) const;

    IntersectData IntersectPoint(const Point& point) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    IntersectData Intersect(const Collider& other) const override;

    bool operator==(Point &point){
        return this->m_parent == point.m_parent;
    }

    glm::vec3 m_point = glm::vec3();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINT_H
