//
// Created by erick on 9/18/18.
//

#include "TerrainBody.h"
#include "../Colliders/TerrainCollider.h"

TerrainBody::TerrainBody()
: PhysicsObject(1.0f,glm::vec3(0,0,0), new TerrainCollider()){
    this->m_type = TERRAIN_BODY_COMPONENT;
}
