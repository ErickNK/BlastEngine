//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GAME_H
#define MORDEROPENGLUDEMYTUTORIAL_GAME_H


#include "Input.h"
#include "../Common/ProfileTimer.h"
#include "Window.h"
#include "Scene.h"

class CoreEngine;

class RenderingEngine;

/**
 * Main game. This is what other games using this engine will extend.
 * */
class Game {
public:
    Game(){};
    ~Game(){};

    /**
     * Figure out and initialize the current scene
     * */
    virtual void Init();

    /**
     * Process the input, and update the objects
     * */
    void ProcessInput(Input* input, float delta);

    /**
     * Update the state of our objects
     * */
    void Update(double time, float delta);

    /**
     * Draw the objects to the screen
     * */
    void Render();

    /**
    * Set engine.
    * */
    inline void SetEngine(CoreEngine* engine) { m_core_engine = engine; }
    void SetCurrentScene(Scene* scene);
    Scene *getCurrentScene() const;
    CoreEngine *getCoreEngine() const;
private:

    CoreEngine* m_core_engine;
    Scene* m_currentScene;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GAME_H
