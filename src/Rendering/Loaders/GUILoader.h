//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUILOADER_H
#define MORDEROPENGLUDEMYTUTORIAL_GUILOADER_H


#include <string>
#include <vector>
#include "../../Core/Entities/GUIEntity.h"

class GUILoader {
public:

    GUILoader();

    bool LoadGUI(std::string directory, GUIEntity* root);

    bool LoadGUI(std::map<Texture*,Transform*> textures, GUIEntity *root);

//    bool LoadGUI(std::vector<std::string> textureLocations, GUIEntity *root);

    void processNode(GUIEntity* root);

    std::vector<Texture*> loadTextures();

    void Clean();

private:
    std::string directory;
    std::vector<Texture*> textures_loaded;
    std::map<Texture*,Transform*> textures_transforms_loaded;
    bool withTexManuallyProvided = false;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUILOADER_H
