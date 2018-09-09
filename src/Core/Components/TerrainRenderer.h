//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERER_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERER_H

#include "GameComponent.h"
#include "../../Rendering/Terrain/Terrain.h"
#include "../../Rendering/Shaders/TerrainShader.h"

class TerrainRenderer : public GameComponent{
public:
    explicit TerrainRenderer(Terrain* terrain) : GameComponent(terrain) {
        m_shader = new TerrainShader();
        m_shader->Init();
        m_shader->setTerrain(terrain);
    }

    virtual void Render(Shader* shader) const
    {
        m_shader->UpdateModel(m_parent->getTransform());


        if (m_parent->getTransform().isNonUnformScaled()) {
            m_shader->UpdateNormalMatrix(
                    glm::mat3(glm::transpose(glm::inverse(m_parent->getTransform().GetModel())))
            );
        } else {
            m_shader->UpdateNormalMatrix(
                    glm::mat3(m_parent->getTransform().GetModel())
            );
        }

        m_parent->getMaterial().UseMaterial(m_shader);

        m_shader->resetDrawingTextureUnits();

        m_parent->getMesh().Draw();
    }

private:
    TerrainShader* m_shader;
};
#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERER_H
