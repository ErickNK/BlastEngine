#version 400

const int MAX_MATERIAL_TEXTURES = 3;

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec4 vCol;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//LIGHTING ---------------------------------------------------

struct Light{
    vec3 colour;
    float ambientIntensity;
};

struct Material{
    sampler2D diffuse_texture[MAX_MATERIAL_TEXTURES];

    int diffuseTextureCount;
};

// ---------------------------------------------------------

//uniform variables -----------------------------------------

uniform Light light;
uniform Material material;

// -----------------------------------------------------------

//other variables -----------------------------------------

vec4 totalDiffuseTexture;
vec4 totalSpecularTexture;

// -----------------------------------------------------------

void CalcTotalDiffuseTexture(){
    totalDiffuseTexture = vec4(1, 1, 1, 1);
    for(int i = 0; i < material.diffuseTextureCount; i++){
        totalDiffuseTexture *= texture(material.diffuse_texture[i], vTexCoord);
    }
}

void main(){

    CalcTotalDiffuseTexture();

    /**
    * Calculate Ambient Light
    * */
    vec4 ambient = (vec4(light.colour, 1.0f) * light.ambientIntensity) * (totalDiffuseTexture * vCol) ;

    colour = ambient;
}