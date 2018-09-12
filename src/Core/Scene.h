//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_SCENE_H

#include <vector>
#include "Entities/LightEntity.h"
#include "Entities/MeshedEntity.h"
#include "Entities/EffectEntity.h"
#include "../Rendering/SkyBox.h"

class LightEntity;
class Game;
class RenderingEngine;

class Scene {
public:

    Scene(Game* game);

    /**
    * Initialize all components required for each scene
    * */
    virtual void Init();

    /**
    * Process the input, and update the objects
    * */
    void ProcessInput(Input* input, float delta);

    /**
     * Update the state of our objects
     * */
    void Update(float delta);

    /**
     * Add new objects to the scene
     * */
    void AddLightToScene(LightEntity* entity);
    void AddMeshedToScene(MeshedEntity* meshed);
    void AddEffectToScene(EffectEntity* effect);
    void AddCamera(Camera *camera);
    void AddSkyBox(SkyBox *skyBox);

    void SetCurrentCamera(int position);
    void SetCurrentSkyBox(int position);

    Game* getGame() const;

    const std::vector<LightEntity *> &getLights() const;

    const std::vector<MeshedEntity *> &getMeshedEntities() const;

    const std::vector<EffectEntity *> &getEffectEntities() const;

    Camera *getCurrentCamera() const;

    SkyBox *getCurrentSkybox();

private:

    /**
     * Reference to the game;
     *
     * */
    Game* m_game;

    Camera* m_current_camera;
    SkyBox* m_current_skybox;

    /**
    * Objects contained in the scene
    * */
    std::vector<Camera*> m_cameras;
    std::vector<SkyBox*> m_skyboxes;
    std::vector<LightEntity*> m_lights;
    std::vector<MeshedEntity*> m_meshed_Entities;
    std::vector<EffectEntity*> m_effect_Entities;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SCENE_H
