//
// Created by erick on 9/14/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H

#include "../../Rendering/Terrain/Terrain.h"
#include "Collider.h"

class AxisAlignedBoundingBox;
class BoundingSphere;
class Plane;

class TerrainCollider : public Collider {
public:
    TerrainCollider();

    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

    IntersectData IntersectAABB(const AxisAlignedBoundingBox& other) const;

    IntersectData IntersectPlane(const Plane& other) const;

    IntersectData IntersectTerrain(const TerrainCollider& other) const;

    IntersectData Intersect(const Collider& other) const;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINCOLLUSIONDETECTION_H
