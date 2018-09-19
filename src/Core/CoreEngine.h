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
    CoreEngine() = default;

    CoreEngine(Window* window, RenderingEngine* renderingEngine, PhysicsEngine* physicsEngine, Game* game, double frameRate) :
            m_frameTimeLimit(1.0/frameRate),
            m_window(window),
            m_renderingEngine(renderingEngine),
            m_physicsEngine(physicsEngine),
            m_game(game) {}

    void Init();
    void Start();
    void Run();
    void Stop();

    //GETTERS AND SETTERS
    inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
    inline Game* GetGame() { return m_game; }
    inline PhysicsEngine* GetPhysicsEngine() { return m_physicsEngine; }
    inline Window* GetWindow(){return m_window;}

    inline void setWindow(Window *m_window) { CoreEngine::m_window = m_window; }
    inline void setRenderingEngine(RenderingEngine *m_renderingEngine) { CoreEngine::m_renderingEngine = m_renderingEngine; }
    inline void setPhysicsEngine(PhysicsEngine *m_physicsEngine) { CoreEngine::m_physicsEngine = m_physicsEngine; }
    inline void setGame(Game *m_game) { CoreEngine::m_game = m_game; }
    inline void setFrameTimeLimit(double m_frameTimeLimit) { CoreEngine::m_frameTimeLimit = m_frameTimeLimit; }

private:
    bool m_shouldRender = false;    //Whether or not the scene should be rendered
    bool m_isRunning = false;       //Whether or not the engine is running
    double m_frameTimeLimit = 1.0 / 60;   //How long, in seconds, one frame should take
    double m_time_since_start = 0.0;   //Time since start of game in seconds

    Window* m_window = nullptr;          //Used to display the game
    RenderingEngine* m_renderingEngine = nullptr; //Used to render the game. Stored as pointer so the user can pass in a derived class.
    PhysicsEngine* m_physicsEngine = nullptr; //Used to simulate physics.
    Game* m_game = nullptr;            //The game itself. Stored as pointer so the user can pass in a derived class.

    ProfileTimer m_sleepTimer;
    ProfileTimer m_swapBufferTimer;
    ProfileTimer m_windowUpdateTimer;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_COREENGINE_H
