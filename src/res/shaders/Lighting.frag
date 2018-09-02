#version 330

//Constant variables -----------------------------------------

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;
const int MAX_MATERIAL_TEXTURES = 3;

// -----------------------------------------------------------

//Input variables ------------------------------------------

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPos;
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
    sampler2D diffuse_texture[MAX_MATERIAL_TEXTURES];
	sampler2D specular_texture[MAX_MATERIAL_TEXTURES];	

	int diffuseTextureCount;
	int specularTextureCount;

    float specularIntensity;
    float shininess;
};

// ---------------------------------------------------------

//uniform variables -----------------------------------------

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int pointLightCount;
uniform int spotLightCount;

uniform Material material;
uniform vec3 cameraPosition;
uniform vec3 cameraDirection;

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

	//Get depth of the fragment relative to the light in orthographic projection.
	float closestDepth = texture(directionalLight.shadowMap, projCoords.xy).r; 
	
	//Get how far (forwards and backwards) from the light the fragment is.
	float currentDepth = projCoords.z; 

	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

	return 0.0f;
}


void CalcTotalDiffuseTexture(){
	totalDiffuseTexture = vec4(1, 1, 1, 1);
    for(int i = 0; i < material.diffuseTextureCount; i++){
		totalDiffuseTexture *= texture(material.diffuse_texture[i], vTexCoord);
    }
}

void CalcTotalSpecularTexture(){
	totalSpecularTexture = vec4(1, 1, 1, 1);
    for(int i = 0; i < material.specularTextureCount; i++){
		totalSpecularTexture *= texture(material.specular_texture[i], vTexCoord);
    }
}

vec4 CalcLightByDirection(Light light, vec3 lightDirection, float shadowFactor){
	vec3 normalizedNormal = normalize(vNormal);

    /**
    * Calculate Ambient Light
    * */
    vec4 ambient = (vec4(light.colour, 1.0f) * light.ambientIntensity) * totalDiffuseTexture ;

    /**
     * Calculate Diffuse light
     * */
    float diffuseFactor = max(dot(normalizedNormal, -lightDirection), 0.0f);

    vec4 diffuse = (vec4(light.colour, 1.0f) * light.diffuseIntensity) * (diffuseFactor * totalDiffuseTexture);

    /**
     * Calculate Specular lighting
     * */
    vec4 specular = vec4(0,0,0,0);
    if (diffuseFactor > 0.0f){ //Only when there is diffuse light

        vec3 fragToEyeVector = normalize(cameraPosition - vFragPos);

        vec3 reflectionVector = normalize(reflect(-lightDirection, normalizedNormal));

        float specularFactor = max(dot(fragToEyeVector, reflectionVector), 0.0f);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);

            specular = (vec4(light.colour, 1.0f) * material.specularIntensity) * (specularFactor * totalSpecularTexture);
        }
    }

    /**
     * MAIN fragment colouring
     * */
    return (ambient + (1.0 - shadowFactor) * (diffuse + specular));

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

vec4 CalcLightBySpot(SpotLight sLight){
    //The straight line between the fragment and the spot light
    vec3 rayToFragDirection = normalize(sLight.base.position - vFragPos);

    /**
    * The Angle between the main direction the spotlight is facing and
    * the straight line from fragment to the spotlight. This will be used
    * to determine if the angle is within the edge of the spotlight (maximum angle
    * between the main direction of the spotlight and the edge of the spotlight rays.
    */
    float FragToSpotDirectionAngle = dot(rayToFragDirection,normalize(-sLight.direction));

    if(FragToSpotDirectionAngle > sLight.edge){ //Its within the edge

        vec4 col = CalcLightByPoint(sLight.base);

        return col * (1.0f - ((1.0f - FragToSpotDirectionAngle)*(1.0f/(1.0f - sLight.edge))));

    }else{ //Not within edge just show ambience

        return (vec4(sLight.base.base.colour, 1.0f) * sLight.base.base.ambientIntensity) * totalDiffuseTexture;

    }
}

vec4 CalcDirectionalLight(){
    return CalcLightByDirection(
		directionalLight.base,
		directionalLight.direction,
		CalcDirectionalLightShadowFactor(directionalLight)
	);
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
	CalcTotalDiffuseTexture();
	CalcTotalSpecularTexture();

    vec4 finalColor = CalcDirectionalLight();
    finalColor += CalcPointLights();
    finalColor += CalcSpotLights();

    /**
     * MAIN fragment colouring
     * */
    colour = finalColor;
}