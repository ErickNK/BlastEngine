#version 330

//Input variables
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;

//output variables
out vec4 colour;

//Lighting
struct DirectionalLight{
    vec3 colour;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
};

struct Material{
    float specularIntensity;
    float shininess;
};

//uniform variables
uniform sampler2D texture0;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPosition;

void main(){
    /**
     * Calculate Ambient Light
     * */
    vec4 ambient = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

    /**
     * Calculate Diffuse light
     * */
    float diffuseFactor = max(dot(normalize(vNormal),normalize(directionalLight.direction)), 0.0f);

    vec4 diffuse = vec4(directionalLight.colour, 1.0f) * diffuseFactor * directionalLight.diffuseIntensity;

    /**
     * Calculate Specular lighting
     * */
    vec4 specular = vec4(0,0,0,0);
    if (diffuseFactor > 0.0f){ //Only when there is diffuse light

        vec3 fragToEyeVector = normalize(cameraPosition - vFragPos);

        vec3 reflectionVector = normalize(reflect(directionalLight.direction, normalize(vNormal)));

        float specularFactor = dot(fragToEyeVector, reflectionVector);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);

            specular = vec4(directionalLight.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }

    /**
     * MAIN fragment colouring
     * */
    colour = /*vec4(0.804, 0.361, 0.361, 1.0)*/ texture2D(texture0, vTexCoord) * (ambient + diffuse + specular);
}