#version 400


//Input variables ------------------------------------------

in vec4 vClipSpace;
in vec2 vTexCoord;
in vec3 vToCameraVector;
in vec3 vFragPos;
in vec4 vCol;

//in vec3 vFromLightVector;

// ---------------------------------------------------------

//output variables ------------------------------------------

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_diffuse;
layout (location = 3) out vec4 out_specular;
layout (location = 4) out vec2 out_material;

// ----------------------------------------------------------

struct Material{
    sampler2D reflectionTexture;
    sampler2D refractionTexture;
    sampler2D refractionDepthTexture;
    sampler2D dudvMap;
    sampler2D normalMap;

    float specularIntensity;
    float fresnelIntensity;
    float shininess;
};

//uniform variables -----------------------------------------

uniform Material material;
uniform float moveFactor;
uniform float waveStrength;
uniform float colorTint;

// -----------------------------------------------------------

void main(){

    vec2 ndc = (vClipSpace.xy / vClipSpace.w) / 2.0 + 0.5;
    vec2 refractTexCoords = vec2(ndc.x,ndc.y);
    vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

    vec3 viewVector = normalize(vToCameraVector);

//DEPTH
    float nearPlane = 0.1;
    float farPlane = 1000.0;
    float depth = texture(material.refractionDepthTexture, refractTexCoords).r;
    //Convert to linear distance from camera
    float floorDistance = 2.0 * nearPlane * farPlane / (farPlane + nearPlane - (2.0 * depth - 1.0) * (farPlane - nearPlane));
    //Get distance to surface of water
    depth = gl_FragCoord.z;
    float waterDistance = 2.0 * nearPlane * farPlane / (farPlane + nearPlane - (2.0 * depth - 1.0) * (farPlane - nearPlane));

    //Get water depth
    float waterDepth = floorDistance - waterDistance;

    //DISTORTION
    vec2 distortedTexCoords = texture(material.dudvMap, vec2(vTexCoord.x + moveFactor, vTexCoord.y)).rg*0.1;
    distortedTexCoords = vTexCoord + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
    vec2 totalDistortion = (texture(material.dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth/5.0, 0.0, 1.0);

    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
    reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);

//NORMAL MAPPING

    //Calculate normals from normal map
    vec4 normalMapColor = texture(material.normalMap, distortedTexCoords);
    vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b * 3.0, normalMapColor.g * 2.0 - 1.0);
    normal = normalize(normal);

//FRESNEL EFFECT
    float refractiveFactor = dot(viewVector, normal);
    refractiveFactor = pow(refractiveFactor, material.fresnelIntensity);
    refractiveFactor = clamp(refractiveFactor,0.0,1.0);

//FINAL
    vec4 refractionColor = texture(material.refractionTexture, refractTexCoords);
    vec4 reflectionColor = texture(material.reflectionTexture, reflectTexCoords);
    vec4 colour = mix(reflectionColor, refractionColor, refractiveFactor);
    colour = mix(colour, vCol, colorTint); //Add blue tint
    colour.a = clamp(waterDepth/0.5, 0.0, 1.0); //rise alpha with depth upto 5

    /**
     * MAIN fragment colouring
     * */
    out_position = vFragPos;
    out_normal = normalize(normal);
    out_diffuse = colour;
    out_specular = vec4(1.0) * vCol; //TODO: load specular colour
    out_material = vec2(material.specularIntensity * clamp(waterDepth/0.5, 0.0, 1.0),material.shininess);
}