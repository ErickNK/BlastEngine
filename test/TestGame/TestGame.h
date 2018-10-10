//
// Created by erick on 9/8/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SLICKDRIVEGAME_H
#define MORDEROPENGLUDEMYTUTORIAL_SLICKDRIVEGAME_H


#include "Scenes/ShadingScene.h"
#include "Scenes/TestScene.h"

class TestGame: public Game{

public:
    TestGame() = default;

    void Init() override{
        auto * scene = new ShadingScene(this);
        scene->Init();
        this->SetCurrentScene(scene);
    }
protected:
private:

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SLICKDRIVEGAME_H
