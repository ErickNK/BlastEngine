#include "AxisAlignedBoundingBox.h"
#include "TerrainCollider.h"
#include "BoundingSphere.h"
#include "Plane.h"

template <class Parent>
bool AxisAlignedBoundingBox<Parent>::IsValid() {
    return m_minExtents.GetX() < m_maxExtents.GetX() && m_minExtents.GetY() < m_maxExtents.GetY() && m_minExtents.GetZ() < m_maxExtents.GetZ();
}
template <class Parent>
void AxisAlignedBoundingBox<Parent>::Fix() {
    if (m_minExtents.GetX() > m_maxExtents.GetX()) {
        Vector3f temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
    if (m_minExtents.GetY() > m_maxExtents.GetY()) {
        Vector3f temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
    if (m_minExtents.GetZ() > m_maxExtents.GetZ()){
        Vector3f temp = m_maxExtents;
        m_maxExtents = m_minExtents;
        m_minExtents = temp;
    }
}

template <class Parent>  template <class OtherParent>
IntersectData AxisAlignedBoundingBox<Parent>::IntersectAABB(const AxisAlignedBoundingBox<OtherParent> & other) const
{
	/**
	* We try all extents and find the max. The wrongly facing extents will return
	* a negative.
	*/
	Vector3f distance1 = other.GetMinExtents() - m_maxExtents;
	Vector3f distance2 = m_minExtents - other.GetMaxExtents();
	Vector3f distances = Vector3f(distance1.Max(distance2));

	float maxDistance = distances.Max();

	return IntersectData(maxDistance < 0, distances);
}

template<class Parent> template <class OtherParent>
IntersectData AxisAlignedBoundingBox<Parent>::IntersectBoundingSphere(const BoundingSphere<OtherParent> &other) const {

	//Find closest point



	return IntersectData(0, Vector3f());
}

template<class Parent> template <class OtherParent>
IntersectData AxisAlignedBoundingBox<Parent>::IntersectPlane(const Plane<OtherParent> &other) const {
	return IntersectData(0, Vector3f());
}

template<class Parent>
IntersectData AxisAlignedBoundingBox<Parent>::IntersectTerrain(const TerrainCollider &other) const {

	return IntersectData(0, Vector3f());
}

template<class Parent>
IntersectData AxisAlignedBoundingBox<Parent>::IntersectPoint(const Point &point) const {

	return {
	(
		(
			point.m_parent.GetX() > m_minExtents.GetX()
		 && point.m_parent.GetY() > m_minExtents.GetY()
		 && point.m_parent.GetZ() > m_minExtents.GetZ()
		)
				 &&
		(
			point.m_parent.GetX() < m_maxExtents.GetX()
		 && point.m_parent.GetY() < m_maxExtents.GetY()
		 && point.m_parent.GetZ() < m_maxExtents.GetZ()
		)
	), Vector3f()};

}

template<class Parent> template <class OtherParent>
IntersectData AxisAlignedBoundingBox<Parent>::Intersect(const Collider<OtherParent> &other) const {

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

template<class Parent>
Point AxisAlignedBoundingBox<Parent>::ClosestPoint(Point &point) {
	Point result;
	for(int i = 0; i < 3; i++){ //For all axis
		if(point.m_parent[i] > m_maxExtents[i]){
			result.m_parent[i] = m_maxExtents[i];
		}else if(point.m_parent[i] < m_minExtents[i]){
			result.m_parent[i] = m_minExtents[i];
		}else{
			result.m_parent[i] = point.m_parent[i];
		}
	}
	return result;
}

