#version 440 core

#include "constants.vert"

//Attribute Pointers -----------------------------------

layout (location = 0) in vec3 position;
layout (location = 4) in ivec3 joint_ids;
layout (location = 5) in vec3 weights;

//------------------------------------------------------

//Output variables ------------------------------------

layout (location = 0) out vec4 vWorldPosition;
out gl_PerVertex{
        vec4 gl_Position;
        float gl_ClipDistance[MAX_CLIP_PLANES];
};

//------------------------------------------------------

//Uniform variables ------------------------------------

uniform bool isAnimated = false;
uniform mat4 model;
uniform mat4 jointTransforms[MAX_JOINTS_PER_MESH];

//---------------------------------------------------------

void main(){

    vec4 totalLocalPos = vec4(0.0);


    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    if(isAnimated){

//        for(int i = 0; i < MAX_WEIGHTS_PER_VERTEX ; i++){

        mat4 jointTransform = jointTransforms[joint_ids[0]];

        vec4 posePosition = (jointTransform * vec4(position, 1.0)) * weights[0];
        totalLocalPos = posePosition  + totalLocalPos;


        jointTransform = jointTransforms[joint_ids[1]];

        posePosition = (jointTransform * vec4(position, 1.0)) * weights[1];
        totalLocalPos = posePosition  + totalLocalPos;


        jointTransform = jointTransforms[joint_ids[2]];

        posePosition = (jointTransform * vec4(position, 1.0)) * weights[2];
        totalLocalPos = posePosition  + totalLocalPos;

//        }

    }else{
        totalLocalPos = vec4(position, 1.0);
    }

    if(totalLocalPos == vec4(0.0)){
        totalLocalPos = vec4(position, 1.0);
    }

    vWorldPosition = model * totalLocalPos;

//    gl_Position = worldPosition;
}
