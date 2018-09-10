//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_COREENGINE_H
#define MORDEROPENGLUDEMYTUTORIAL_COREENGINE_H

#include "Window.h"
#include "../Common/Util.h"
#include "Game.h"
#include "../Common/ProfileTimer.h"
#include "../Rendering/RenderingEngine.h"
#include "../Physics/PhysicsEngine.h"

class CoreEngine {
public:
    CoreEngine(Window* window, RenderingEngine* renderingEngine, Game* game, double frameRate) :
            m_isRunning(false),
            m_shouldRender(false),
            m_frameTimeLimit(1.0/frameRate),
            m_window(window),
            m_renderingEngine(renderingEngine),
            m_game(game)
    {
        m_game->SetEngine(this);
        m_game->Init();
    }

    void Start();
    void Run();
    void Stop();
    inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
    inline Game* GetGame() { return m_game; }
    inline PhysicsEngine* GetPhysicsEngine() { return m_physicsEngine; }
private:
    bool m_shouldRender;    //Whether or not the scene should be rendered
    bool m_isRunning;       //Whether or not the engine is running
    double m_frameTimeLimit;   //How long, in seconds, one frame should take
    Window* m_window;          //Used to display the game
    RenderingEngine* m_renderingEngine; //Used to render the game. Stored as pointer so the user can pass in a derived class.
    PhysicsEngine* m_physicsEngine;
    Game* m_game;            //The game itself. Stored as pointer so the user can pass in a derived class.

    ProfileTimer m_sleepTimer;
    ProfileTimer m_swapBufferTimer;
    ProfileTimer m_windowUpdateTimer;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_COREENGINE_H
