#include <utility>

//
// Created by erick on 9/15/18.
//

#include "TextureAtlas.h"

TextureAtlas::TextureAtlas() :
Texture(){}

TextureAtlas::TextureAtlas(std::string fileLocation, TextureTypeEnum typeName, int Index, int numberOfRows) :
Texture(std::move(fileLocation), typeName),
texture_index(Index),
number_of_rows(numberOfRows){}

TextureAtlas::TextureAtlas(std::string path, std::string directory, TextureTypeEnum typeName, int Index, int numberOfRows) :
Texture(std::move(path), std::move(directory),typeName),
texture_index(Index),
number_of_rows(numberOfRows){}

int TextureAtlas::getNumberOfRows() const {
    return number_of_rows;
}

void TextureAtlas::setNumberOfRows(int number_of_rows) {
    TextureAtlas::number_of_rows = number_of_rows;
}

int TextureAtlas::getTextureIndex() const {
    return texture_index;
}

void TextureAtlas::setTextureIndex(int texture_index) {
    TextureAtlas::texture_index = texture_index;
}

float TextureAtlas::getTextureXOffset() {
    int column = texture_index % number_of_rows;
    return (float)column/(float)number_of_rows;
}

float TextureAtlas::getTextureYOffset(){
    int row = texture_index / number_of_rows;
    return (float)row/(float)number_of_rows;
}
