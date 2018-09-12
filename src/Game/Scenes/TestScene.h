//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H

#include "../../Core/Scene.h"
#include "../../Rendering/Loaders/MeshedLoader.h"

class TestScene : public Scene{
public:
    TestScene(Game* game): Scene(game){}

    void Init() override;

    void CreateLighting();

    void CreateCharacters();

    void CreateTerrain();

    void SetupCamera();

    void SetupSkyBox();


private:
    MeshedLoader * m_meshed_loader;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
