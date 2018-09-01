#pragma once
class IntersectData
{
public:
	IntersectData(bool doesIntersect, const Vector3f& direction) : 
		m_doesIntersect(doesIntersect), 
		m_direction(direction) {};

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return m_direction.Length(); }
	inline const Vector3f& GetDirection() const { return m_direction; }
private:
	const bool m_doesIntersect;
	const Vector3f m_direction;
};

