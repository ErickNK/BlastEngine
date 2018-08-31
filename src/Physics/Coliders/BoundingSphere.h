#pragma once
#include "../../Core/math3d.h"
#include "IntersectData.h"

class BoundingSphere
{
public:
	BoundingSphere(const Vector3f& center, float radius) :
		m_center(center),
		m_radius(radius) {};

	IntersectData IntersectBoundingSphere(const BoundingSphere& other);

	inline const Vector3f& GetCenter() const { return m_center; }
	inline float GetRadius() const { return m_radius; }
private:
	const Vector3f m_center;
	const float m_radius;
};

