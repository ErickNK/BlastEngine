#include "Collider.h"

IntersectData Collider::Intersect(const Collider& other) const
{
	if (m_type == TYPE_BOUNDINGSPHERE && other.m_type == TYPE_BOUNDINGSPHERE) {
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	std::cerr << "Error: Collisions not implemented between specified colliders" << std::endl;
	exit(1);
	return IntersectData(false,0);
}