//
// Created by erick on 9/16/18.
//

#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "../../Rendering/Terrain/Terrain.h"
#include "../Objects/PhysicsObject.h"

TerrainCollider::TerrainCollider()
: Collider(TYPE_TERRAIN){}

IntersectData TerrainCollider::IntersectBoundingSphere(const BoundingSphere& other) const
{
    return IntersectData(false, glm::vec3());
}

IntersectData TerrainCollider::IntersectAABB(const AxisAlignedBoundingBox &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData TerrainCollider::IntersectPlane(const Plane &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData TerrainCollider::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, glm::vec3());
}

IntersectData TerrainCollider::Intersect(const Collider& other) const
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
        case NUM_TYPES:break;
        default:{
            std::cerr << "Error: Collisions not implemented between specified colliders" << std::endl;
            return {false,glm::vec3()};
        }
    }
}


