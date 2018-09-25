//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H
#define MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H

#include <vector>
#include "../Material.h"

class GUIMaterial{
public:
    GUIMaterial() = default;

    explicit GUIMaterial(std::vector<Texture*>& textures);

    void AddGUI(Texture* gui);

    void UseMaterial(Shader * shader);

    const std::vector<Texture *> &getTextures() const;

private:
    std::vector<Texture*> textures;
    Texture* activeTexture = nullptr;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIMATERIAL_H
