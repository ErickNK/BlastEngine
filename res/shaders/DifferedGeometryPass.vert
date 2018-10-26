#version 440 core

#include "constants.vert"

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in ivec3 joint_ids;
layout (location = 5) in vec3 weights;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec3 vFragPos;
layout(location = 3) out vec4 vCol;


out gl_PerVertex{
        vec4 gl_Position;
        float gl_ClipDistance[MAX_CLIP_PLANES];
};

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;

uniform bool isAnimated = false;
uniform bool hasFakeLighting;
uniform int textureAtlasNumOfRows;
uniform int directionalLightCount;
uniform int pointLightCount;
uniform int spotLightCount;
uniform int lightsCount;

uniform vec2 textureAtlasOffset;
uniform vec4 clipPlanes[MAX_CLIP_PLANES];
uniform mat4 jointTransforms[MAX_JOINTS_PER_MESH];

//---------------------------------------------------------

//Other varibles-----------------------------------------



//---------------------------------------------------------

void main(){

    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    if(isAnimated){

//        for(int i = 0; i < MAX_WEIGHTS_PER_VERTEX ; i++){

        if(joint_ids[0] >= 0) {
            mat4 jointTransform = jointTransforms[joint_ids[0]];

            vec4 posePosition = (jointTransform * vec4(position, 1.0)) * weights[0];
            totalLocalPos = posePosition  + totalLocalPos;

            vec4 worldNormal = (jointTransform * vec4(normal, 0.0)) * weights[0];
            totalNormal = worldNormal + totalNormal;
        }

        if(joint_ids[1] >= 0){
            mat4 jointTransform = jointTransforms[joint_ids[1]];

            vec4 posePosition = (jointTransform * vec4(position, 1.0)) * weights[1];
            totalLocalPos = posePosition  + totalLocalPos;

            vec4 worldNormal = (jointTransform * vec4(normal, 0.0)) * weights[1];
            totalNormal = worldNormal + totalNormal;
        }

        if(joint_ids[2] >= 0){
            mat4 jointTransform = jointTransforms[joint_ids[2]];

            vec4 posePosition = (jointTransform * vec4(position, 1.0)) * weights[2];
            totalLocalPos = posePosition  + totalLocalPos;

            vec4 worldNormal = (jointTransform * vec4(normal, 0.0)) * weights[2];
            totalNormal = worldNormal + totalNormal;
        }
//        }

    }else{
        totalLocalPos = vec4(position, 1.0);
        totalNormal = vec4(normal, 0.0);
    }

    if(totalLocalPos == vec4(0.0)){
        totalLocalPos = vec4(position, 1.0);
        totalNormal = vec4(normal, 0.0);
    }

    vec4 worldPosition = model * totalLocalPos;
    vec4 viewPosition = view * worldPosition;
    vec4 clipPosition = projection * viewPosition;

    gl_Position = clipPosition;

    /**
     * Clip planes
     * */
    for (int i = 0; i < MAX_CLIP_PLANES; i++){
        gl_ClipDistance[i] = dot(worldPosition,clipPlanes[i]);
    }

    //Check for fake lighting
    vec3 actualNormal = totalNormal.xyz;
    if(hasFakeLighting){
        actualNormal = vec3(0.0,1.0,0.0);
    }

    /**
     * Calculate for texture Atlas
     * */
    vTexCoord = (texCoord/textureAtlasNumOfRows) + textureAtlasOffset;

    /**
     * Directly pass the diffuse color of each vertex
     * */
    vCol = color;

    /**
     * The normal is just a direction from the vertex. The position of the vertex is
     * the origin of the normal. If we rotate the vertex the direction might change, if
     * we scale the vertex the direction might also change, but moving the vertex will not
     * change the direction. We multiply with model to apply transformation and disable translation(moving).
     *
     * We inverse and transpose to avoid scaling skewing our normal direction, thus accounting for
     * non-uniform scaling. We then convert to mat3 to disable translation. The mat3 will multiplication
     * will return a vec3 which is what we want.
     * */
    vNormal = normalMatrix * actualNormal;

    /**
     * We need the world position of a vertex/Fragment. This is the position after transformation
     * has been applied only. The positions of other fragments will be interpolated as values are
     * sent to the fragment shader.
     *
     * We apply swizzling (vec4).xyz to get a vec3.
     * */
    vFragPos = (model * totalLocalPos).xyz;
}