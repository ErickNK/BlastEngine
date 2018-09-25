#version 400

//Constant variables -----------------------------------------

const int MAX_MATERIAL_TEXTURES = 3;

// -----------------------------------------------------------

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;
in vec4 vCol;

// ---------------------------------------------------------

//output variables ------------------------------------------

layout(location = 0) out vec4 colour;

// ----------------------------------------------------------

//LIGHTING ---------------------------------------------------

struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct PointLight{
    Light base;
    vec3 position;
    float attenuationConstant;
    float attenuationLinear;
    float attenuationQuadratic;
};

struct SpotLight{
    PointLight base;
    vec3 dir;
    float edge;
};

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

uniform SpotLight spotLight;
uniform Material material;
uniform vec3 cameraPosition;
uniform vec3 cameraDirection;
uniform bool allowCellShading;
uniform int cellShadingLevels;

// -----------------------------------------------------------

//other variables -----------------------------------------

vec4 totalDiffuseTexture;
vec4 totalSpecularTexture;

// -----------------------------------------------------------

void CalcTotalDiffuseTexture(){
    totalDiffuseTexture = vec4(1, 1, 1, 1);
    if(material.diffuseTextureCount == 0){
        totalDiffuseTexture = vec4(0, 0, 0, 0);
    }else {
        for (int i = 0; i < material.diffuseTextureCount; i++) {
            totalDiffuseTexture *= texture(material.diffuse_texture[i], vTexCoord);
        }
    }
}

void CalcTotalSpecularTexture(){
    totalSpecularTexture = vec4(1, 1, 1, 1);
    if(material.specularTextureCount == 0){
        totalSpecularTexture = vec4(0, 0, 0, 0);
    }else {
        for (int i = 0; i < material.specularTextureCount; i++) {
            totalSpecularTexture *= texture(material.specular_texture[i], vTexCoord);
        }
    }
}

vec4 CalcLightByDirection(Light light, vec3 lightDirection, float shadowFactor){
    vec3 normalizedNormal = normalize(vNormal);

    //CellShading
    float actualDiffuseIntensity = light.diffuseIntensity;
    float actualSpecularIntensity = material.specularIntensity;
    if(allowCellShading){
        float level = floor(light.diffuseIntensity * cellShadingLevels);
        actualDiffuseIntensity = level / cellShadingLevels;

        level = floor(material.specularIntensity * cellShadingLevels);
        actualSpecularIntensity = level / cellShadingLevels;
    }

    /**
     * Calculate Diffuse light
     * */
    float diffuseFactor = max(dot(normalizedNormal, -lightDirection), 0.0f);

    vec4 diffuse = (vec4(light.colour, 1.0f) * actualDiffuseIntensity) * (diffuseFactor * totalDiffuseTexture * vCol);

    /**
     * Calculate Specular lighting
     * */
    vec4 specular = vec4(0,0,0,0);
    if (diffuseFactor > 0.0f){ //Only when there is diffuse light

        vec3 fragToEyeVector = normalize(cameraPosition - vFragPos);

        vec3 reflectionVector = normalize(reflect(lightDirection, normalizedNormal));

        float specularFactor = max(dot(fragToEyeVector, reflectionVector), 0.0f);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);

            specular = (vec4(light.colour, 1.0f) * actualSpecularIntensity) * (specularFactor * totalSpecularTexture * vCol);
        }
    }

    /**
     * MAIN fragment colouring
     * */
    return /*(1.0 - shadowFactor) **/ (diffuse + specular);

}

vec4 CalcLightByPoint(PointLight pLight){
    vec3 lightDirection =  vFragPos - pLight.position; //Get LightToFrag vector as direction

    float distance = length(lightDirection); //We get the magnitude of LightToFrag vector

    lightDirection = normalize(lightDirection); //For a qualified unit vector

    vec4 col = CalcLightByDirection(pLight.base, lightDirection,0.0f);

    float attenuation = pLight.attenuationQuadratic * distance * distance +
                        pLight.attenuationLinear * distance +
                        pLight.attenuationConstant;

    return (col / attenuation);
}

vec4 CalcLightBySpot(){
    //The straight line between the fragment and the spot light
    vec3 rayToFragDirection = normalize(vFragPos - spotLight.base.position);

    /**
    * The Angle between the main direction the spotlight is facing and
    * the straight line from fragment to the spotlight. This will be used
    * to determine if the angle is within the edge of the spotlight (maximum angle
    * between the main direction of the spotlight and the edge of the spotlight rays.
    */
    float FragToSpotDirectionAngle = dot(rayToFragDirection,normalize(spotLight.dir));

    if(FragToSpotDirectionAngle > spotLight.edge){ //Its within the edge

        vec4 col = CalcLightByPoint(spotLight.base);

        return col * (1.0f - ((1.0f - FragToSpotDirectionAngle)*(1.0f/(1.0f - spotLight.edge))));

    }else{ //Not within edge just show ambience

        return vec4(0,0,0,0);

    }

}


void main(){
    CalcTotalDiffuseTexture();

    CalcTotalSpecularTexture();

    //Check transparency
    if(material.hasTransparency && ((totalDiffuseTexture).a < 0.1 && (totalSpecularTexture).a < 0.1)){
        discard;
    }

    /**
     * MAIN fragment colouring
     * */
    colour = CalcLightBySpot();
}