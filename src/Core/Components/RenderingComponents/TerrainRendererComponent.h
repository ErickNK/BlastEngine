//
// Created by erick on 9/12/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/TerrainShader.h"
#include "../MeshedComponent.h"

class TerrainRendererComponent: public MeshedComponent {
public:
    void RenderTerrain(RenderingEngine* engine) const {
        auto * shader = (TerrainShader*) engine->GetShader(TERRAIN_SHADER);

        engine->SetCurrentShader(TERRAIN_SHADER);

        shader->Bind();

            shader->setTerrain((Terrain *)(m_meshedEntity));

            shader->UpdateView(*engine->getCurrentScene()->getCurrentCamera());

            shader->UpdateProjection(engine->getProjection());

            m_meshedEntity->RenderAll(shader);

        shader->UnBind();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TERRAINRENDERERCOMPONENT_H
