//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINSHADER_H

#include "Shader.h"
#include "../Terrain/Terrain.h"

class TerrainShader : public Shader{
public:
    TerrainShader();

    void CreateUniforms() override;

    void setTerrain(Terrain* terrain);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINSHADER_H
