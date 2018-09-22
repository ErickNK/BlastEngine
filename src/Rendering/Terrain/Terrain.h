//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H

#include "../../Common/CommonValues.h"
#include "../../Core/Entities/MeshedEntity.h"

class TerrainRendererComponent;
class RenderingEngine;

//TODO: create a loader class to handle loading the terrain
class Terrain : public MeshedEntity{

public:
    Terrain() = default;

    Terrain(int gridX, int gridY,std::map<TextureTypeEnum, std::string> textureLocations);

    ~Terrain();

    void RenderTerrain(RenderingEngine* engine);

    float getTerrainHeight(float x, float z) const;
private:
    std::map<TextureTypeEnum, std::string> m_textureLocations;

    TerrainRendererComponent* m_terrain_renderer;

    float SIZE = 800, x , z ;

    //TODO:: use vectors to get correct size of heights on one edge
    float** heights;

    int height_map_width,height_map_height,height_map_bitDepth;

    int HEIGHT_MAX = 40;

    int MAX_PIXEL_COLOR = 256 * 256 * 256;

    unsigned char * height_map;

    bool LoadHeightMap();

    void UnLoadHeightMap();

    void AddComponents();

    void InitTerrain();

    float getPixelHeight(int x, int y);

    glm::vec3 calculateNormal(int x, int y);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAIN_H
