#version 400 core

//Constant variables -----------------------------------------

// -----------------------------------------------------------

//Input variables ------------------------------------------

in vec2 vTexCoord;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//uniform variables -----------------------------------------

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

// -----------------------------------------------------------

void main(){
    vec4 blendMapColor = texture(blendMap,vTexCoord); //Specifies which texture to use
    /**
     * Tile the texture after getting the blendMapColor
     * */
    vec2 tiledTexCoord = vTexCoord * 60.0f;

    //Background
    float backgroundTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
    vec4 backgroundTextureColor = texture(backgroundTexture,tiledTexCoord) * backgroundTextureAmount;

    //R
    vec4 rTextureColor = texture(rTexture,tiledTexCoord) * blendMapColor.r;

    //G
    vec4 gTextureColor = texture(gTexture,tiledTexCoord) * blendMapColor.g;

    //B
    vec4 bTextureColor = texture(bTexture,tiledTexCoord) * blendMapColor.b;


    /**
     * MAIN fragment colouring
     * */
    colour = (backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor) * 0.4;
}