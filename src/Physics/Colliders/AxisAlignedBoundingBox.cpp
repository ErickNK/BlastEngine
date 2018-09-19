#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include <glm/gtx/component_wise.hpp>

bool AxisAlignedBoundingBox::IsValid() {
    return m_minExtents.m_point.x < m_maxExtents.m_point.x && m_minExtents.m_point.y < m_maxExtents.m_point.y && m_minExtents.m_point.z < m_maxExtents.m_point.z;
}

void AxisAlignedBoundingBox::Fix() {
    if (m_minExtents.m_point.x > m_maxExtents.m_point.x) {
        Point temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
    if (m_minExtents.m_point.y > m_maxExtents.m_point.y) {
        Point temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
    if (m_minExtents.m_point.z > m_maxExtents.m_point.z){
        Point temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
}

IntersectData AxisAlignedBoundingBox::IntersectAABB(const AxisAlignedBoundingBox & other) const
{
	/**
	* We try all extents and find the max. The wrongly facing extents will return
	* a negative.
	*/
	glm::vec3 distance1 = other.GetMinExtents().m_point - m_maxExtents.m_point;
    glm::vec3 distance2 = m_minExtents.m_point - other.GetMaxExtents().m_point;
    glm::vec3 distances = glm::max(distance1,(distance2));

	float maxDistance = glm::compMax(distances);

	return IntersectData(maxDistance < 0, distances);
}

IntersectData AxisAlignedBoundingBox::IntersectBoundingSphere(const BoundingSphere &other) const {

	//Find closest point
	return IntersectData(0, glm::vec3());
}

IntersectData AxisAlignedBoundingBox::IntersectPlane(const Plane &other) const {
	return IntersectData(0, glm::vec3());
}

IntersectData AxisAlignedBoundingBox::IntersectTerrain(const TerrainCollider &other) const {

	return IntersectData(0, glm::vec3());
}

IntersectData AxisAlignedBoundingBox::IntersectPoint(const Point &point) const {

	return {
	(
		(
			point.m_point.x > m_minExtents.m_point.x
		 && point.m_point.y > m_minExtents.m_point.y
		 && point.m_point.z > m_minExtents.m_point.z
		)
				 &&
		(
			point.m_point.x < m_maxExtents.m_point.x
		 && point.m_point.y < m_maxExtents.m_point.y
		 && point.m_point.z < m_maxExtents.m_point.z
		)
	), glm::vec3()};

}

IntersectData AxisAlignedBoundingBox::Intersect(const Collider &other) const {

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

Point AxisAlignedBoundingBox::ClosestPoint(Point &point) {
	Point result;
	for(int i = 0; i < 3; i++){ //For all axis
		if((point.m_point)[i] > m_maxExtents.m_point[i]){
			(result.m_point)[i] = m_maxExtents.m_point[i];
		}else if((point.m_point)[i] < m_minExtents.m_point[i]){
			(result.m_point)[i] = m_minExtents.m_point[i];
		}else{
			(result.m_point)[i] = (point.m_point)[i];
		}
	}
	return result;
}

