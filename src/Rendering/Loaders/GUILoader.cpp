#include <utility>

#include <utility>

//
// Created by erick on 9/15/18.
//

#include "GUILoader.h"
#include "../../Common/Util.h"

GUILoader::GUILoader() = default;

void GUILoader::Clean(){
    withTexManuallyProvided = false;

    this->textures_loaded.clear();
}

//TODO: allow multiple textures per GUIEntity
bool GUILoader::LoadGUI(std::map<Texture*,Transform*> textures, GUIEntity *root) {
    withTexManuallyProvided = true;
    this->textures_transforms_loaded = std::move(textures);

    this->processNode(root);

    Clean();
    return true;
}

//bool GUILoader::LoadGUI(std::vector<std::string> textureLocations, GUIEntity *root) {
//    withTexManuallyProvided = true;
//
//    for (const std::string &x : textureLocations) {
//        this->textures_loaded.push_back(new Texture(x, GUI_TEXTURE)); //Keep so we don't reload it.
//    }
//
//    this->processNode(root);
//
//    Clean();
//    return true;
//}

bool GUILoader::LoadGUI(std::string directory, GUIEntity *root) {
    GUILoader::directory = std::move(directory);


    this->processNode(root);

    Clean();
    return true;
}

void GUILoader::processNode(GUIEntity* root) {
    root->setTransform(*new Transform());

    if (withTexManuallyProvided){
        for(auto &p : textures_transforms_loaded){
            auto * child = new GUIEntity();

            GUIMaterial material = *new GUIMaterial();
            material.AddGUI(p.first);

            child->setMaterial(material);

            child->setTransform(*p.second);

            root->AddChild(child);
        }

    }else{
        std::vector<Texture *> textures = loadTextures();
        root->setMaterial(*new GUIMaterial(textures));
    }
}

std::vector<Texture *> GUILoader::loadTextures() {
    std::vector<Texture *> textures;

    std::vector<std::string> files;

    if(Util::getDirFiles(directory,files) == 0)
        for (auto & p : files) {

            GLboolean skip = false;

            //Search for already loaded textures.
            for (GLuint j = 0; j < this->textures_loaded.size(); j++) {
                if (this->textures_loaded[j]->GetFileLocation() == p) { //if already loaded
                    textures.push_back(this->textures_loaded[j]);
                    skip = true;
                    break;
                }
            }

            //TODO: configure Texture class
            if (!skip) { //If not loaded
                Texture* texture = new Texture("../res/textures/gui/health.png",GUI_TEXTURE);;
                textures.push_back(texture);

                this->textures_loaded.push_back(texture); //Keep so we don't reload it.
            }
        }

    return textures;
}