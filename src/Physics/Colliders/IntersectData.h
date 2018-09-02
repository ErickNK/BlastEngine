#ifndef INTERSECTDATA_INCLUDED_H
#define INTERSECTDATA_INCLUDED_H

#include "../../Core/math3d.h"

class IntersectData
{
public:
	IntersectData(const bool doesIntersect, const Vector3f& direction) : 
		m_doesIntersect(doesIntersect), 
		m_direction(direction) {}

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return m_direction.Length(); }
	inline const Vector3f& GetDirection() const { return m_direction; }
private:
	const bool m_doesIntersect;
	const Vector3f m_direction;
};

#endif