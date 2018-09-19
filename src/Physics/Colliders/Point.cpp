#include "Point.h"
#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "../Objects/PhysicsObject.h"

IntersectData Point::IntersectBoundingSphere(const BoundingSphere& other) const {
    return other.IntersectPoint(*this);
}

IntersectData Point::IntersectAABB(const AxisAlignedBoundingBox& other) const {
    return other.IntersectPoint(*this);
}

IntersectData Point::IntersectPlane(const Plane& other) const {
    return other.IntersectPoint(*this);
}

IntersectData Point::IntersectTerrain(const TerrainCollider &other) const {
    IntersectData result;

    float terrainHeight = ((Terrain*)other.GetParent()->getParent())->getTerrainHeight(this->m_point.x,this->m_point.z);

    bool interaction = this->m_point.y < terrainHeight; // Lower than terrain

    if(interaction){
        result = IntersectData(true, (this->m_point - glm::vec3(this->m_point.x,terrainHeight,this->m_point.z)));
    }else{
        result = IntersectData(false, glm::vec3());
    }

    return result;
}

IntersectData Point::IntersectPoint(const Point &point) const {
    //If point is the same
    if(this->m_point == point.m_point) return {true, glm::vec3(0,0,0)};
    else {
        //get direction
        return {false, point.m_point - this->m_point};
    }
}

IntersectData Point::Intersect(const Collider& other) const
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

void Point::Update() {
    this->m_point = m_parent->getParent()->getTransform().GetPos();
}
