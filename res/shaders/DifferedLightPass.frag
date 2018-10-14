#version 400

#include "constants.vert"

//Input variables ------------------------------------------

in vec2 vTexCoord;

// ---------------------------------------------------------

//output variables ------------------------------------------

layout(location = 0) out vec4 colour;

// ----------------------------------------------------------

//LIGHTING ---------------------------------------------------

struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
    bool allowCellShading;
    int cellShadingLevels;
};

struct DirectionalLight{
    Light base;
    vec3 direction;

    sampler2D shadowMap;
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
    vec3 direction;
    float edge;
};

// ---------------------------------------------------------

//uniform variables -----------------------------------------

uniform DirectionalLight directionalLight[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int directionalLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

uniform vec3 cameraPosition;
uniform vec3 cameraDirection;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D materialTexture;
uniform sampler2D depthTexture;

// -----------------------------------------------------------

//other variables -----------------------------------------

vec3 vFragPos;
vec3 vNormal;
vec4 vDiffuse;
vec4 vSpecular;
vec2 vMaterial;
float vDepth;

// -----------------------------------------------------------

vec4 CalcLightByDirection(Light light, vec3 lightDirection){

    //CellShading
    float actualAmbientIntensity = light.ambientIntensity;
    float actualDiffuseIntensity = light.diffuseIntensity;
    float actualSpecularIntensity = vMaterial.x;
    if(light.allowCellShading){
        float level = floor(light.diffuseIntensity * light.cellShadingLevels);
        actualDiffuseIntensity = level / light.cellShadingLevels;

        level = floor( vMaterial.x * light.cellShadingLevels);
        actualSpecularIntensity = level / light.cellShadingLevels;

        level = floor(light.ambientIntensity * light.cellShadingLevels);
        actualAmbientIntensity = level / light.cellShadingLevels;
    }

    /**
    * Calculate Ambient Light
    * */
    vec4 ambient = (vec4(light.colour, 1.0f) * actualAmbientIntensity) * vDiffuse ;

    /**
     * Calculate Diffuse light
     * */
    float diffuseFactor = max(dot(vNormal, -lightDirection), 0.0f);

    vec4 diffuse = (vec4(light.colour, 1.0f) * actualDiffuseIntensity) * (diffuseFactor * vDiffuse);

    /**
     * Calculate Specular lighting
     * */
    vec4 specular = vec4(0,0,0,0);
    if (diffuseFactor > 0.0f){ //Only when there is diffuse light

        vec3 fragToEyeVector = normalize(cameraPosition - vFragPos);

        vec3 reflectionVector = normalize(reflect(lightDirection, vNormal));

        float specularFactor = max(dot(fragToEyeVector, reflectionVector), 0.0f);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, vMaterial.y);

            specular = (vec4(light.colour, 1.0f) * actualSpecularIntensity) * (specularFactor * vSpecular);
        }
    }

    /**
     * MAIN fragment colouring
     * */
    return (ambient + /*(1.0 - shadowFactor) **/ (diffuse + specular));

}

vec4 CalcLightByPoint(PointLight pLight){
    vec3 lightDirection =  vFragPos - pLight.position; //Get LightToFrag vector as direction

    float distance = length(lightDirection); //We get the magnitude of LightToFrag vector

    lightDirection = normalize(lightDirection); //For a qualified unit vector

    vec4 col = CalcLightByDirection(pLight.base, lightDirection);

    float attenuation = pLight.attenuationQuadratic * distance * distance +
                        pLight.attenuationLinear * distance +
                        pLight.attenuationConstant;

    return (col / attenuation);
}

vec4 CalcLightBySpot(SpotLight sLight){
    //The straight line between the fragment and the spot light
    vec3 rayToFragDirection = normalize(vFragPos - sLight.base.position);

    /**
    * The Angle between the main direction the spotlight is facing and
    * the straight line from fragment to the spotlight. This will be used
    * to determine if the angle is within the edge of the spotlight (maximum angle
    * between the main direction of the spotlight and the edge of the spotlight rays.
    */
    float FragToSpotDirectionAngle = dot(rayToFragDirection,normalize(sLight.direction));

    if(FragToSpotDirectionAngle > sLight.edge){ //Its within the edge

        vec4 col = CalcLightByPoint(sLight.base);

        return col * (1.0f - ((1.0f - FragToSpotDirectionAngle)*(1.0f/(1.0f - sLight.edge))));

    }else{ //Not within edge just show ambience

        return (vec4(sLight.base.base.colour, 1.0f) * sLight.base.base.ambientIntensity) * vDiffuse;

    }
}

vec4 CalcDirectionalLights(){
    vec4 totalColor = vec4(0,0,0,0);
    for (int i = 0; i < directionalLightCount; ++i) {
        totalColor += CalcLightByDirection(directionalLight[i].base, directionalLight[i].direction);
    }
    return totalColor;
}

vec4 CalcPointLights(){
    vec4 totalColor = vec4(0, 0, 0, 0);
    for(int i = 0; i < pointLightCount; i++){
        totalColor += CalcLightByPoint(pointLights[i]);
    }
    return totalColor;
}

vec4 CalcSpotLights(){
    vec4 totalColor = vec4(0, 0, 0, 0);
    for(int i = 0; i < spotLightCount; i++){
        totalColor += CalcLightBySpot(spotLights[i]);
    }
    return totalColor;
}

void main(){

    vFragPos = texture(positionTexture,vTexCoord).rgb;
    vNormal = texture(normalTexture,vTexCoord).rgb;
    vDiffuse = texture(diffuseTexture,vTexCoord);
    vSpecular = texture(specularTexture,vTexCoord);
    vMaterial = texture(materialTexture,vTexCoord).rg;
    vDepth = texture(depthTexture,vTexCoord).r;

    vec4 finalColor = CalcDirectionalLights();
    finalColor += CalcPointLights();
    finalColor += CalcSpotLights();

    /**
     * MAIN fragment colouring
     * */
    colour = CalcDirectionalLights();
}