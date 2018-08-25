#version 330

//Input variables
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

//output variables
out vec4 colour;

//Constants
const int MAX_POINT_LIGHTS = 3;

//Lighting
struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight{
    Light base;
    vec3 direction;
};

struct PointLight{
    Light base;
    vec3 position;
    float attenuationConstant;
    float attenuationLinear;
    float attenuationQuadratic;
};

struct Material{
    float specularIntensity;
    float shininess;
};

//uniform variables

//LIGHTING
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightsCount;

uniform Material material;
uniform vec3 cameraPosition;

//TEXTURES
uniform sampler2D texture0;

vec4 CalcLightByDirection(Light light, vec3 direction){
    /**
    * Calculate Ambient Light
    * */
    vec4 ambient = vec4(light.colour, 1.0f) * light.ambientIntensity;

    /**
     * Calculate Diffuse light
     * */
    float diffuseFactor = max(dot(normalize(vNormal),normalize(direction)), 0.0f);

    vec4 diffuse = vec4(light.colour, 1.0f) * diffuseFactor * light.diffuseIntensity;

    /**
     * Calculate Specular lighting
     * */
    vec4 specular = vec4(0,0,0,0);
    if (diffuseFactor > 0.0f){ //Only when there is diffuse light

        vec3 fragToEyeVector = normalize(cameraPosition - vFragPos);

        vec3 reflectionVector = normalize(reflect(direction, normalize(vNormal)));

        float specularFactor = dot(fragToEyeVector, reflectionVector);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);

            specular = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }

    /**
     * MAIN fragment colouring
     * */
    return (ambient + diffuse + specular);

}

vec4 CalcDirectionalLight(){
    return CalcLightByDirection(directionalLight.base,directionalLight.direction);
}

vec4 CalcPointLights(){
    vec4 totalColor = vec4(0, 0, 0, 0);
    for(int i = 0; i < (pointLightsCount + 1); i++){
        vec3 direction = vFragPos - pointLights[i].position; //Get LightToFrag vector as direction

        float distance = length(direction); //We get the magnitude of LightToFrag vector

        direction = normalize(direction); //For a qualified unit vector

        vec4 col = CalcLightByDirection(pointLights[i].base, direction);

        float attenuation = pointLights[i].attenuationQuadratic * distance * distance +
                            pointLights[i].attenuationLinear * distance +
                            pointLights[i].attenuationConstant;

        totalColor +=  (col / attenuation);
    }
    return totalColor;
}

void main(){
    vec4 finalColor = CalcDirectionalLight();
    finalColor += CalcPointLights();

    /**
     * MAIN fragment colouring
     * */
    colour = texture2D(texture0, vTexCoord) * finalColor;
}