#pragma once
class IntersectData
{
public:
	IntersectData(bool doesIntersect, float distance) : 
		m_doesIntersect(doesIntersect), 
		m_distance(distance) {};

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return m_distance; }

private:
	const bool m_doesIntersect;
	const float m_distance;
};

