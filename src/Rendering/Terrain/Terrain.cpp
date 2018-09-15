#include <utility>

//
// Created by erick on 9/9/18.
//

#include "Terrain.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../../Core/Components/RenderingComponents/TerrainRendererComponent.h"
#include "../../Common/Util.h"

Terrain::Terrain(int gridX, int gridZ,std::map<TextureTypeEnum, std::string> textureLocations) :
    m_textureLocations(std::move(textureLocations))
{
    x = gridX * SIZE;
    z = gridZ * SIZE;
    InitTerrain();
};

void Terrain::InitTerrain() {
    if(LoadHeightMap()) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture*> textures;

        int VERTEX_COUNT = height_map_height;

        heights = new float*[height_map_height];
        for (int i = 0;i<height_map_height;i++)
            heights[i] = new float[height_map_height];

        for (int i = 0; i < VERTEX_COUNT; i++) {
            for (int j = 0; j < VERTEX_COUNT; j++) {
                float height = getPixelHeight(j, i);
                heights[j][i] = height;

                vertices.emplace_back(
                        glm::vec3((float) j / ((float) VERTEX_COUNT - 1) * SIZE, height ,
                                  (float) i / ((float) VERTEX_COUNT - 1) * SIZE),
                        glm::vec2((float) j / ((float) VERTEX_COUNT - 1), (float) i / ((float) VERTEX_COUNT - 1)),
                        calculateNormal(j, i)
                );
            }
        }
        for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
            for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
                int topLeft = (gz * VERTEX_COUNT) + gx;
                int topRight = topLeft + 1;
                int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
                int bottomRight = bottomLeft + 1;
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }

        m_mesh = Mesh(vertices, vertices.size(), indices, indices.size());
        for (auto const &x : m_textureLocations) {
            textures.push_back(new Texture(x.second, x.first));
        }
        m_material = Material(0.0, 0.0, textures);
        m_transform = Transform();

        m_transform.GetPos().x = x;
        m_transform.GetPos().z = z;

        AddComponents();
        UnLoadHeightMap();
    }
}

bool Terrain::LoadHeightMap(){

    this->height_map = stbi_load(m_textureLocations[HEIGHT_MAP_TEXTURE].c_str(),&height_map_width,&height_map_height,&height_map_bitDepth, 4);

    if(this->height_map == nullptr){
        std::cerr << "Error: Height map loading failed for:"<< m_textureLocations[HEIGHT_MAP_TEXTURE] << std::endl;
        return false;
    }

    return true;
}

void Terrain::UnLoadHeightMap() {
    stbi_image_free(this->height_map);
}

void Terrain::AddComponents(){
    //ADD COMPONENTS
    auto * renderer = new MeshedRendererComponent();
    this->AddComponent(renderer);

    m_terrain_renderer = new TerrainRendererComponent();
    m_terrain_renderer->SetParent(this);
}

void Terrain::RenderTerrain(RenderingEngine *engine) {
    m_terrain_renderer->RenderTerrain(engine);
}

float Terrain::getPixelHeight(int x, int y) {
    if(x < 0 || x >= height_map_width || y < 0 || y >= height_map_height) return 0;

    float height = height_map[(y * height_map_width + x) * height_map_bitDepth];
//    height += MAX_PIXEL_COLOR/2.0f;
//    height /= MAX_PIXEL_COLOR/2.0f;
    height *= ((height / 255.0f) - 0.5f);
    return  height;
}

glm::vec3 Terrain::calculateNormal(int x, int z) {
    float heightL = getPixelHeight(x-1,z);
    float heightR = getPixelHeight(x+1,z);
    float heightU = getPixelHeight(x,z-1);
    float heightD = getPixelHeight(x,z+1);
    glm::vec3 normal = glm::vec3(heightL-heightR,2.0f,heightD-heightU);
    glm::normalize(normal);
    return normal;
}

Terrain::~Terrain() {
//    for (int i = 0;i<height_map_height;i++)
//        delete[] heights[i];
//    delete[] heights;
}

float Terrain::getTerrainHeight(float x, float z) {
    float terrainX = x - this->x;
    float terrainZ = z - this->z;
    float gridSquareSize = SIZE/((float) sizeof(heights) - 1);
    int gridX = (int) floor(terrainX / gridSquareSize);
    int gridZ = (int) floor(terrainZ / gridSquareSize);

    if(gridX >= sizeof(heights) - 1 || gridZ >= sizeof(heights) - 1 || gridX < 0 || gridZ < 0){
        return 0;
    }
    float xCoord = (fmod(terrainX, gridSquareSize))/gridSquareSize;
    float zCoord = (fmod(terrainZ, gridSquareSize))/gridSquareSize;
    float answer;
    //Figure out which triangle object is standing on. Then use BarryCentric interpolation to
    //figure out height on point where object is standing.
    if (xCoord <= (1-zCoord)) {
        answer = Util::barryCentric(
                    glm::vec3(0, heights[gridX][gridZ], 0),
                    glm::vec3(1, heights[gridX + 1][gridZ], 0),
                    glm::vec3(0, heights[gridX][gridZ + 1], 1),
                    glm::vec2(xCoord, zCoord)
                );
    } else {
        answer = Util::barryCentric(
                   glm::vec3(1, heights[gridX + 1][gridZ], 0),
                   glm::vec3(1, heights[gridX + 1][gridZ + 1], 1),
                   glm::vec3(0, heights[gridX][gridZ + 1], 1),
                   glm::vec2(xCoord, zCoord)
               );
    }
    return  answer;
}





