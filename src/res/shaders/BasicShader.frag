#version 330

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//LIGHTING ---------------------------------------------------

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

struct SpotLight{
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material{
    float specularIntensity;
    float shininess;
};

// ---------------------------------------------------------

//Constant variables -----------------------------------------

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

// -----------------------------------------------------------

//uniform variables -----------------------------------------

uniform sampler2D texture0;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int pointLightCount;
uniform int spotLightCount;

uniform Material material;
uniform vec3 cameraPosition;
uniform vec3 cameraDirection;

// -----------------------------------------------------------

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

vec4 CalcLightByPoint(PointLight pLight){
     vec3 direction = vFragPos - pLight.position; //Get LightToFrag vector as direction

    float distance = length(direction); //We get the magnitude of LightToFrag vector

    direction = normalize(direction); //For a qualified unit vector

    vec4 col = CalcLightByDirection(pLight.base, direction);

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
    float FragToSpotDirectionAngle = dot(rayToFragDirection,sLight.direction);

    if(FragToSpotDirectionAngle > sLight.edge){ //Its within the edge

        vec4 col = CalcLightByPoint(sLight.base);

        return col * (1.0f - ((1.0f - FragToSpotDirectionAngle)*(1.0f/(1.0f - sLight.edge))));

    }else{ //Not within edge

        return vec4(0,0,0,0);

    }
}

vec4 CalcDirectionalLight(){
    return CalcLightByDirection(directionalLight.base,directionalLight.direction);
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
    vec4 finalColor = CalcDirectionalLight();
    finalColor += CalcPointLights();
    finalColor += CalcSpotLights();

    /**
     * MAIN fragment colouring
     * */
    colour = texture(texture0, vTexCoord) * finalColor;
}