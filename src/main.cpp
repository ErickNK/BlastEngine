#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>

#include "Common/CommonValues.h"
#include "Core/Window.h"
#include "Core/CoreEngine.h"
#include "Game/SlickDriveGame.h"

int main() {
    Window window = Window(1366,768);
    window.Initialize();

    CoreEngine engine;
    RenderingEngine renderer(&window);
    PhysicsEngine physicsEngine;
    SlickDriveGame game;

    engine.setWindow(&window);
    engine.setPhysicsEngine(&physicsEngine);
    engine.setRenderingEngine(&renderer);
    engine.setGame(&game);
	engine.setFrameTimeLimit(1.0/60.0);

	engine.Init();
	engine.Start();
    return 0;
}