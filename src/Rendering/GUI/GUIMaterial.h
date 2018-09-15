//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H
#define MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H

#include <vector>
#include "../Material.h"
#include "GUITexture.h"

class GUIMaterial{
public:
    GUIMaterial() = default;

    explicit GUIMaterial(std::vector<GUITexture*>& textures);

    void AddGUI(GUITexture* gui);

    void UseMaterial(Shader * shader);

    const std::vector<GUITexture *> &getTextures() const;

private:
    std::vector<GUITexture*> textures;
    GUITexture* activeTexture = nullptr;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H
