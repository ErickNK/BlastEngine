#ifndef INTERSECTDATA_INCLUDED_H
#define INTERSECTDATA_INCLUDED_H

#include <glm/glm.hpp>
#include <cstring>
#include "../../Common/math3d.h"

class IntersectData
{
public:
	IntersectData() = default;

    IntersectData(const bool doesIntersect, const glm::vec3& direction) :
		m_doesIntersect(doesIntersect), 
		m_direction(direction) {}

//    IntersectData& operator=(IntersectData&& other){
////		char* temp[sizeof(IntersectData) / sizeof(char)];
////		memcpy(temp, this, sizeof(IntersectData));
////		memcpy(this, &other, sizeof(IntersectData));
////		memcpy(&other, temp, sizeof(IntersectData));
//        return other;
//	}

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return glm::length(m_direction); }
	inline const glm::vec3& GetDirection() const { return m_direction; }

	const bool getInsideCollider() const {
		return m_inside_collider;
	}

	const bool getBehindCollider() const {
		return m_behind_collider;
	}

	void setInsideCollider(bool m_inside_collider) {
		IntersectData::m_inside_collider = m_inside_collider;
	}

	void setBehindCollider(bool m_behind_collider) {
		IntersectData::m_behind_collider = m_behind_collider;
	}

    IntersectData inverse() {
    	m_direction = -m_direction;
        return *this;
    }

private:
	bool m_doesIntersect = false;
	glm::vec3 m_direction;
	bool m_inside_collider = false;
	bool m_behind_collider = false;
};

#endif