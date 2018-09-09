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
        //Game is initialized here because this is the point where all rendering systems
        //are initialized, and so creating meshes/textures/etc. will not fail due
        //to missing context.
        m_game->Init(m_window);

        //We're telling the game about this engine so it can send the engine any information it needs
        //to the various subsystems.
        m_game->SetEngine(this);
    }

    void Start();
    void Run();
    void Stop();
    inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
private:
    bool m_shouldRender;    //Whether or not the scene should be rendered
    bool m_isRunning;       //Whether or not the engine is running
    double m_frameTimeLimit;   //How long, in seconds, one frame should take
    Window* m_window;          //Used to display the game
    RenderingEngine* m_renderingEngine; //Used to render the game. Stored as pointer so the user can pass in a derived class.
    Game* m_game;            //The game itself. Stored as pointer so the user can pass in a derived class.

    ProfileTimer m_sleepTimer;
    ProfileTimer m_swapBufferTimer;
    ProfileTimer m_windowUpdateTimer;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_COREENGINE_H
