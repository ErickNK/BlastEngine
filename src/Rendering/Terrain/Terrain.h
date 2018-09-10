//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H

#include "../../Common/CommonValues.h"
#include "../../Core/Entities/MeshedEntity.h"

class Terrain : public MeshedEntity{

public:
    Terrain() = default;

    Terrain(int gridX, int gridY,std::map<TextureTypeEnum, std::string> textureLocations);

    void InitTerrain();
private:
    std::map<TextureTypeEnum, std::string> m_textureLocations;

    float m_size = 800, x , z ;

    int m_vertex_count = 128;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H
