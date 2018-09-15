//
// Created by erick on 9/12/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/TerrainShader.h"
#include "../EntityComponent.h"

class TerrainRendererComponent: public EntityComponent<Terrain,RenderingEngine> {
public:
    void RenderTerrain(RenderingEngine* engine) const {
        auto * shader = (TerrainShader*) engine->GetShader(TERRAIN_SHADER);

        engine->SetCurrentShader(TERRAIN_SHADER);

        shader->Bind();

            shader->setTerrain(m_entity);

            shader->UpdateCamera(*engine->getCurrentScene()->getCurrentCamera());

            m_entity->RenderAll(shader);

        shader->UnBind();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
