#include <utility>

#include <utility>

//
// Created by erick on 9/15/18.
//

#include "GUITexture.h"

GUITexture::GUITexture()
: Texture(){}

GUITexture::GUITexture(std::string fileLocation, TextureTypeEnum typeName)
: Texture(std::move(fileLocation), typeName) {}

GUITexture::GUITexture(std::string path, std::string directory, TextureTypeEnum typeName)
: Texture(std::move(path), std::move(directory), typeName) {}
