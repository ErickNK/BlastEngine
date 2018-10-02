//
// Created by erick on 9/12/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/TerrainShader.h"
#include "../EntityComponent.h"

class TerrainRendererComponent: public EntityComponent<Terrain> {
public:
    void Render(RenderingEngine* engine) const override {
        auto * shader = (TerrainShader*) engine->BindShader(TERRAIN_SHADER);

            shader->setTerrain(m_entity);

            shader->UpdateCamera(*engine->getCurrentScene()->getCurrentCamera());

            m_entity->RenderAll(engine);

        engine->UnBindShader(TERRAIN_SHADER);
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
