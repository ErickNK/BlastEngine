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
#include "../Rendering/Terrain/Terrain.h"
#include "MousePicker.h"
#include "../Physics/Objects/RigidBody.h"
#include "../Animation/AnimatedEntity.h"

class GUIEntity;
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
    void AddTerrain(Terrain *terrain);
    void AddGUI(GUIEntity *gui);
    void AddMousePicker(MousePicker *picker);
    void AddPhysicsObject(PhysicsObject* object);
    void AddAnimatedEntity(AnimatedEntity* enitity);

    void SetCurrentCamera(int position);
    void SetCurrentSkyBox(int position);
    void SetCurrentGUI(int position);

    Game* getGame() const;

    const std::vector<LightEntity *> &getLights() const;

    const std::vector<GUIEntity *> getGUIs() const;

    const std::vector<Terrain *> &getTerrains() const;

    const std::vector<MeshedEntity *> &getMeshedEntities() const;

    const std::vector<EffectEntity *> &getEffectEntities() const;

    const std::vector<AnimatedEntity *> &getAnimatedEntities() const;

    std::vector<PhysicsObject *> &getPhysicsObjects();

    Camera *getCurrentCamera() const;

    SkyBox *getCurrentSkybox();

    GUIEntity *getCurrentGUI();

protected:

    /**
     * Reference to the game;
     *
     * */
    Game* m_game;

    Camera* m_current_camera = nullptr;
    SkyBox* m_current_skybox = nullptr;
    GUIEntity* m_current_gui = nullptr;
    MousePicker* m_current_mouse = nullptr;

    /**
    * Objects contained in the scene
    * */
    std::vector<GUIEntity*> m_guis;
    std::vector<AnimatedEntity*> m_animated_Entities;
    std::vector<Camera*> m_cameras;
    std::vector<SkyBox*> m_skyboxes;
    std::vector<LightEntity*> m_lights;
    std::vector<Terrain*> m_terrains;
    std::vector<MeshedEntity*> m_meshed_Entities;
    std::vector<EffectEntity*> m_effect_Entities;
    std::vector<PhysicsObject*> m_physics_object;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SCENE_H
