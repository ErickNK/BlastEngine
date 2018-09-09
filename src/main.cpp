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

    SlickDriveGame game;

	Window window = Window(1366,768);
    window.Initialize();

	RenderingEngine renderer(&window);

	CoreEngine engine(&window, &renderer, &game, 1000);
	engine.Start();


    return 0;
}