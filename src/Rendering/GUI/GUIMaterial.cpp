//
// Created by erick on 9/15/18.
//

#include "GUIMaterial.h"

GUIMaterial::GUIMaterial(std::vector<GUITexture *> &textures)
: textures(textures){}

void GUIMaterial::AddGUI(GUITexture* gui) {
    textures.push_back(gui);
}

const std::vector<GUITexture *> &GUIMaterial::getTextures() const {
    return textures;
}

void GUIMaterial::UseMaterial(Shader * shader) {
    glUniform1i(shader->getUniforms()["gui_texture"], 0);
    if(activeTexture != nullptr){
        activeTexture->Bind(0);
    }else if(!textures.empty()){
        textures[0]->Bind(0);
    }
}
