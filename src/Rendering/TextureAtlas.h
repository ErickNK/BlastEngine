//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TEXTUREATLAS_H
#define MORDEROPENGLUDEMYTUTORIAL_TEXTUREATLAS_H


#include "Texture.h"

class TextureAtlas : public Texture {
public:
    /**
    * Empty Constructor
    * */
    TextureAtlas();

    /**
     * Constructor. Load a texture from storage.
     * */
    TextureAtlas(std::string fileLocation, TextureTypeEnum typeName, int Index, int numberOfRows);

    TextureAtlas(std::string path, std::string directory, TextureTypeEnum typeName, int Index, int numberOfRows);

    int getNumberOfRows() const;

    void setNumberOfRows(int number_of_rows);

    int getTextureIndex() const;

    void setTextureIndex(int texture_index);

    float getTextureXOffset();

    float getTextureYOffset();

private:
    int number_of_rows = 1;
    int texture_index = 0;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TEXTUREATLAS_H
