//
// Created by erick on 9/14/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H

#include "../../Rendering/Terrain/Terrain.h"
#include "Collider.h"


template <class Parent> class AxisAlignedBoundingBox;
template <class Parent> class BoundingSphere;
template <class Parent> class Plane;

class TerrainCollider : public Collider<Terrain> {
    TerrainCollider();

    template <class OtherParent>
    IntersectData IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const;

    template <class OtherParent>
    IntersectData IntersectAABB(const AxisAlignedBoundingBox<OtherParent>& other) const;

    template <class OtherParent>
    IntersectData IntersectPlane(const Plane<OtherParent>& other) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    template <class OtherParent>
    IntersectData Intersect(const Collider<OtherParent>& other) const;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H
