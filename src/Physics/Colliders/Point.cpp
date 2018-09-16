#include "Point.h"
#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"

template <class OtherParent>
IntersectData Point::IntersectBoundingSphere(const BoundingSphere<OtherParent>& other) const {
    return other.IntersectPoint(*this);
}

template <class OtherParent>
IntersectData Point::IntersectAABB(const AxisAlignedBoundingBox<OtherParent> &other) const {
    return other.IntersectPoint(*this);
}

template <class OtherParent>
IntersectData Point::IntersectPlane(const Plane<OtherParent> &other) const {
    return other.IntersectPoint(*this);
}

IntersectData Point::IntersectTerrain(const TerrainCollider &other) const {
    IntersectData result;

    float terrainHeight = other.GetParent().getTerrainHeight(this->m_parent.GetX(),this->m_parent.GetY());

    bool interaction = this->m_parent.GetY() < terrainHeight;

    if(interaction){
        result = IntersectData(true, (this->m_parent - Vector3f(this->m_parent.GetX(),terrainHeight,this->m_parent.GetZ())));
    }else{
        result = IntersectData(false, Vector3f());
    }

    return result;
}

IntersectData Point::IntersectPoint(const Point &point) const {
    //If point is the same
    if(this->m_parent == point.m_parent) return {true, Vector3f(0,0,0)};
    else {
        //get direction
        return {false, point.m_parent - this->m_parent};
    }
}

template <class OtherParent>
IntersectData Point::Intersect(const Collider<OtherParent>& other) const
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

