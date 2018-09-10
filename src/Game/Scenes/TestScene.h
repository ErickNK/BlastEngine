//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H

#include "../../Core/Scene.h"

class TestScene : public Scene{
public:
    TestScene(Game* game): Scene(game){}

    void Init() override;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
