//
// Created by erick on 9/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SCREEN_H
#define MORDEROPENGLUDEMYTUTORIAL_SCREEN_H


#include "../../Core/Entities/MeshedEntity.h"
#include <vector>
#include "../Material.h"
#include "../Texture.h"
#include "../Mesh.h"
#include "../RenderingEngine.h"

class ScreenMesh : public Mesh{
public:
    ScreenMesh() = default;

    ScreenMesh(std::vector<glm::vec2> positions, unsigned int numVertices);

    void Draw() override;

    void InitScreenMesh();

    void Bind() const;

    void UnBind() const;

private:
    std::vector<glm::vec2> positions;
};

class ScreenMaterial{
public:
    ScreenMaterial() = default;

    explicit ScreenMaterial(Texture* texture);

    void SetTexture(Texture* texture);

    void UseMaterial(Shader * shader);

private:
    Texture* m_texture = nullptr;
};

class Screen : public MeshedEntity{
public:
    Screen();

    ~Screen() override;

    void SetTexture(Texture* texture);

    void Render(RenderingEngine *engine);

protected:
    std::vector<EntityComponent<MeshedEntity>> m_components;

    ScreenMesh m_screen_mesh;
    ScreenMaterial m_screen_material;
};



#endif //MORDEROPENGLUDEMYTUTORIAL_SCREEN_H
