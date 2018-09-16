//
// Created by erick on 9/16/18.
//

#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"

TerrainCollider::TerrainCollider()
: Collider(TYPE_TERRAIN){}

template <class OtherParent>
IntersectData TerrainCollider::IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const
{
    return IntersectData(false, Vector3f());
}

template <class OtherParent>
IntersectData TerrainCollider::IntersectAABB(const AxisAlignedBoundingBox<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

template <class OtherParent>
IntersectData TerrainCollider::IntersectPlane(const Plane<OtherParent> &other) const {
    return IntersectData(false, Vector3f());
}

IntersectData TerrainCollider::IntersectTerrain(const TerrainCollider &other) const {
    return IntersectData(false, Vector3f());
}

template <class OtherParent>
IntersectData TerrainCollider::Intersect(const Collider<OtherParent>& other) const
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
        }
        case NUM_TYPES:break;
        default:{
            std::cerr << "Error: Collisions not implemented between specified colliders" << std::endl;
            return {false,0};
        }
    }
}


