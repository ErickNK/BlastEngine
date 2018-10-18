#version 400 core

#include "constants.vert"

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;
in vec4 vCol;

// ---------------------------------------------------------

//output variables ------------------------------------------

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_diffuse;
layout (location = 3) out vec4 out_specular;
layout (location = 4) out vec2 out_material;

// ----------------------------------------------------------

//LIGHTING ---------------------------------------------------

struct Material{
    sampler2D diffuse_texture[MAX_MATERIAL_TEXTURES];
    sampler2D specular_texture[MAX_MATERIAL_TEXTURES];

    int diffuseTextureCount;
    int specularTextureCount;

    float specularIntensity;
    float shininess;

    bool hasTransparency;
};

// ---------------------------------------------------------

//uniform variables -----------------------------------------

uniform Material material;
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
    out_position = vFragPos;
    out_normal = normalize(vNormal);
    out_diffuse = (backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor) * vCol;
    out_specular = vec4(1.0f) * vCol; //TODO: load specular colour
    out_material = vec2(material.specularIntensity,material.shininess);
}