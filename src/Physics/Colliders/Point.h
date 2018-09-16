//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINT_H

#include <glm/glm.hpp>
#include "Collider.h"


template <class Parent> class AxisAlignedBoundingBox;
template <class Parent> class BoundingSphere;
template <class Parent> class Plane;
class TerrainCollider;

class Point : public Collider<Vector3f>{
public:
    Point(): Collider<Vector3f>(TYPE_POINT){};

    Point(float x, float y, float z): Collider<Vector3f>(TYPE_POINT){
        m_parent = Vector3f(x,y,z);
    }

    Point(Vector3f vec): Collider<Vector3f>(TYPE_POINT){
        m_parent = vec;
    }

    template <class OtherParent>
    IntersectData IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const;

    template <class OtherParent>
    IntersectData IntersectAABB(const AxisAlignedBoundingBox<OtherParent>& other) const;

    template <class OtherParent>
    IntersectData IntersectPlane(const Plane<OtherParent>& other) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    template <class OtherParent>
    IntersectData Intersect(const Collider<OtherParent>& other) const;

    IntersectData IntersectPoint(const Point &point) const;

private:
    bool operator==(Point &point){
        return this->m_parent == point.m_parent;
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINT_H
