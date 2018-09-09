//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GAME_H
#define MORDEROPENGLUDEMYTUTORIAL_GAME_H


#include "Input.h"
#include "../Common/ProfileTimer.h"
#include "GameObject.h"
#include "Window.h"

class CoreEngine;

class RenderingEngine;

class Game {
public:
    Game(){};
    ~Game(){};

    virtual void Init(const Window* window) {}

    /**
     * Process the input, and update the objects
     * */
    void ProcessInput(const Input* input, float delta);

    /**
     * Update the state of our objects
     * */
    void Update(float delta);

    /**
     * Draw the objects to the screen
     * */
    void Render(RenderingEngine* renderingEngine);

    /**
     * Get reference variable to root object.
     * */
    GameObject &getRootObject();

    /**
    * Set engine.
    * */
    inline void SetEngine(CoreEngine* engine) { m_root.SetEngine(engine); }

    //PROFILING
    inline double DisplayInputTime(double dividend) { return m_inputTimer.DisplayAndReset("Input Time: ", dividend); }
    inline double DisplayUpdateTime(double dividend) { return m_updateTimer.DisplayAndReset("Update Time: ", dividend); }
protected:
    void AddToScene(GameObject* child) { m_root.AddChild(child); }
private:
    ProfileTimer m_updateTimer;
    ProfileTimer m_inputTimer;

    GameObject m_root;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GAME_H
