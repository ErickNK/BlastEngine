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
    TerrainRendererComponent() : EntityComponent(TERRAIN_RENDERER_COMPONENT) {}

    void Render(RenderingEngine* engine) const override {
        auto * shader = (TerrainShader*) engine->PushShader(TERRAIN_SHADER);

            m_entity->RenderAll(engine);

        engine->PopShader();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
