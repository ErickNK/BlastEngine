#version 400

//Constant variables -----------------------------------------

const int MAX_MATERIAL_TEXTURES = 3;

// -----------------------------------------------------------

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;
in vec4 vCol;

in vec4 vDirectionalLightSpacePosition;

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

    sampler2D shadowMap;
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

uniform DirectionalLight directionalLight;
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


float CalcDirectionalLightShadowFactor(DirectionalLight directionalLight){

    //Convert into normalized device coordinates (-1,1)
    vec3 projCoords = vDirectionalLightSpacePosition.xyz / vDirectionalLightSpacePosition.w;
    //Convert to 0-1 range. Which is what depth range is
    projCoords = (projCoords * 0.5) + 0.5;

    //Get how far (forwards and backwards) from the light the fragment is.
    float currentDepth = projCoords.z;

    //Deal with shadow acne
    vec3 normalizedNormal = normalize(vNormal);
    vec3 normalizedLightDir = normalize(-directionalLight.direction);
    float bias = max(0.005 * (1 - dot(normalizedNormal,normalizedLightDir)), 0.0005);

    //PCF
    float shadow = 0.0f;
    vec2 texelSize = 1.0 / textureSize(directionalLight.shadowMap, 0); //find out how big a unit texel is.

    //We sample all the first texels around this fragment's texel. Forming a cube.
    for(int x = -1 /*Start at further left of the exact x texel of this fragment*/;
        x <= 1 /*Upto the right*/;
        ++x){
        for(int y = -1/*Start at further top of the exact y texel of this fragment*/;
            y <= 1 /*Upto the bottom*/; ++y){
            /*
             * Get depth of the fragment relative to the light in orthographic projection.
             * Each texel in the shadow map contains depth data in the .r attribute instead
             * of color like a normal texture.
             * */
            float pcfDepth = texture(
                    directionalLight.shadowMap,
                    projCoords.xy + vec2(x,y) * texelSize /*Get the exact texel in the current loop. Remember
                * the .xy only point to the current fragments texel not the one we want in the current
                * loop. */
            ).r;
            //Deal with shadow acne
            shadow += currentDepth > pcfDepth ? 1.0 : 0.0; /*Accumulate the average shadow.*/
        }
    }

    shadow /= 9.0f; /*Find average of the shadows we are collecting from the sample*/

    if(projCoords.z > 1.0){ //For points beyond the light space/ beyond the far plane
        shadow = 0.0; //Disable shadow and just say there is total light.
    }

    return shadow;
}

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


vec4 CalcDirectionalLight(){
    return CalcLightByDirection(
            directionalLight.base,
            directionalLight.direction,
            CalcDirectionalLightShadowFactor(directionalLight)
    );
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
    colour = CalcDirectionalLight();
}