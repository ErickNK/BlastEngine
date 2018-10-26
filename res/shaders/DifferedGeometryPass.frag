#version 440 core

#include "constants.vert"

//Input variables ------------------------------------------

layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec3 vFragPos;
layout(location = 3) in vec4 vCol;


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

// -----------------------------------------------------------

//other variables -----------------------------------------

vec4 totalDiffuseTexture;
vec4 totalSpecularTexture;

// -----------------------------------------------------------

void CalcTotalDiffuseTexture(){
    totalDiffuseTexture = vec4(1, 1, 1, 1);
    if(material.diffuseTextureCount == 0){
        totalDiffuseTexture = vec4(1, 1, 1, 1);
    }else {
        for (int i = 0; i < material.diffuseTextureCount; i++) {
            totalDiffuseTexture *= texture(material.diffuse_texture[i], vTexCoord);
        }
    }
}

void CalcTotalSpecularTexture(){
    totalSpecularTexture = vec4(1, 1, 1, 1);
    if(material.specularTextureCount == 0){
        totalSpecularTexture = vec4(1, 1, 1, 1);
    }else {
        for (int i = 0; i < material.specularTextureCount; i++) {
            totalSpecularTexture *= texture(material.specular_texture[i], vTexCoord);
        }
    }
}

void main(){

    CalcTotalDiffuseTexture();

    CalcTotalSpecularTexture();

    //Check transparency
    if(material.hasTransparency && ((totalDiffuseTexture).a < 0.1 && (totalSpecularTexture).a < 0.1)){
        discard;
    }

    out_position = vFragPos;
    out_normal = normalize(vNormal);
    out_diffuse = totalDiffuseTexture * vCol;
    out_specular = totalSpecularTexture * vCol; //TODO: load specular colour
    out_material = vec2(material.specularIntensity,material.shininess);
}