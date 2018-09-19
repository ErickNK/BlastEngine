//
// Created by erick on 9/18/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINBODY_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINBODY_H


#include "glm/glm.hpp"
#include "../../Core/Entities/MeshedEntity.h"
#include "../Colliders/Collider.h"
#include "../Forces/Force.h"
#include "PhysicsObject.h"

class Terrain;

class TerrainBody: public PhysicsObject {
public:
    /**
	* Creates a RigidBody in a usable state.
	*
	* @param collider A collider representing the shape and position of the
	*                   object used for collusions. Should be in allocated memory.
	* @param velocity How fast this object is moving and in what direction.
	*/
    TerrainBody();

};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINBODY_H
