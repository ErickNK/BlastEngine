#include <utility>

//
// Created by erick on 9/9/18.
//

#include "Terrain.h"
#include "../../Core/Components/MeshedRendererComponent.h"
#include "../../Core/Components/TerrainRendererComponent.h"

Terrain::Terrain(int gridX, int gridZ,std::map<TextureTypeEnum, std::string> textureLocations) :
    m_textureLocations(std::move(textureLocations))
{
    x = gridX * m_size;
    z = gridZ * m_size;
    InitTerrain();
};

void Terrain::InitTerrain() {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for(int i=0;i<m_vertex_count;i++){
        for(int j=0;j<m_vertex_count;j++){
            vertices.emplace_back(
                    glm::vec3((float)j/((float)m_vertex_count - 1) * m_size,0,(float)i/((float)m_vertex_count - 1) * m_size),
                    glm::vec2((float)j/((float)m_vertex_count - 1),(float)i/((float)m_vertex_count - 1)),
                    glm::vec3(0,1,0)
            );
        }
    }
    for(int gz=0;gz<m_vertex_count-1;gz++){
        for(int gx=0;gx<m_vertex_count-1;gx++){
            int topLeft = (gz*m_vertex_count)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*m_vertex_count)+gx;
            int bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    m_mesh = Mesh(vertices,vertices.size(),indices,indices.size());
    for (auto const& x : m_textureLocations) {
        Texture texture = *new Texture(x.second, x.first);
        textures.push_back(texture);
    }
    m_material = Material(0.0,0.0,textures);
    m_transform = Transform();

    m_transform.GetPos().x = x;
    m_transform.GetPos().z = z;

    //ADD COMPONENTS
    auto * renderer = new MeshedRendererComponent();
    this->AddComponent(renderer);

    m_terrain_renderer = new TerrainRendererComponent();
    m_terrain_renderer->SetParent(this);
}

void Terrain::RenderTerrain(RenderingEngine *engine) {
    m_terrain_renderer->RenderTerrain(engine);
}

