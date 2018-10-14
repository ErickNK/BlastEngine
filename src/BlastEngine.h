//
// Created by erick on 10/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ENGINE_H
#define MORDEROPENGLUDEMYTUTORIAL_ENGINE_H

#include "Common/CommonValues.h"
#include "Core/Window.h"
#include "Core/CoreEngine.h"

class BlastEngine {
public:
    BlastEngine() = default;
    
    void PlayGame(Game& game){
        //TODO: auto detect screen resolution
        Window window(1366,768);
        RenderingEngine renderingEngine;
        PhysicsEngine physicsEngine;
        CoreEngine coreEngine;

        coreEngine.setWindow(&window);
        coreEngine.setPhysicsEngine(&physicsEngine);
        coreEngine.setRenderingEngine(&renderingEngine);
        coreEngine.setGame(&game);
        coreEngine.setFrameTimeLimit(1.0/100.0);

        //TODO: Add error checking in initialization
        if(coreEngine.Init()){
            coreEngine.Start();
        }
        coreEngine.Stop();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ENGINE_H
