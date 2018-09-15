//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUITEXTURE_H
#define MORDEROPENGLUDEMYTUTORIAL_GUITEXTURE_H


#include "../Texture.h"
#include "../Transform.h"

class GUITexture : public Texture{
public:
    /**
 * Empty Constructor
 * */
    GUITexture();

    /**
     * Constructor. Load a texture from storage.
     * */
    GUITexture(std::string fileLocation, TextureTypeEnum typeName);

    GUITexture(std::string path, std::string directory, TextureTypeEnum typeName);
private:
    /**
     * The position represents the center of the gui texture quad. The scale represents
     * the x and y size of the gui texture quad.
     * */
    Transform m_transform;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUITEXTURE_H
