//
// Created by erick on 10/10/18.
//

#ifndef BLASTENGINE_SCREEN_H
#define BLASTENGINE_SCREEN_H


#include "../../Core/Entities/MeshedEntity.h"
#include <vector>
#include "../Material.h"
#include "../Texture.h"
#include "../Mesh.h"
#include "../RenderingEngine.h"

class DifferedScreenMesh : public Mesh{
public:
    DifferedScreenMesh() = default;

    DifferedScreenMesh(std::vector<glm::vec2> positions, unsigned int numVertices);

    void Draw() override;

    void InitDifferedScreenMesh();

private:
    std::vector<glm::vec2> positions;
};

class DifferedScreenMaterial{
public:
    DifferedScreenMaterial() = default;

    explicit DifferedScreenMaterial(std::vector<Texture*>& textures);

    void AddTexture(Texture* texture);

    void SetTextures(std::vector<Texture*> texs);

    void UseMaterial(Shader * shader);

private:
    std::vector<Texture*> textures;
};

class DifferedScreen : public MeshedEntity{
public:
    DifferedScreen();

    ~DifferedScreen() override;

    void SetTextures(std::vector<Texture*> texs);

    void Render(RenderingEngine *engine) override;

    void AddTexture(Texture *texture);

protected:
    std::vector<EntityComponent<MeshedEntity>> m_components;

    DifferedScreenMesh m_screen_mesh;
    DifferedScreenMaterial m_screen_material;
};


#endif //BLASTENGINE_SCREEN_H
