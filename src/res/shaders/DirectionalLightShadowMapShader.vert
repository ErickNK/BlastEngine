#version 400

//Const ------------------------------------------------

const int MAX_JOINTS_PER_MESH = 50;//max joints allowed in a skeleton
const int MAX_WEIGHTS_PER_VERTEX = 3;//max number of joints that can affect a vertex

//------------------------------------------------------

//Attribute Pointers -----------------------------------

layout (location = 0) in vec3 position;
layout (location = 4) in ivec3 joint_ids;
layout (location = 5) in vec3 weights;

//------------------------------------------------------

//Output variables ------------------------------------

out vec4 vClipPosition;

//------------------------------------------------------

//Uniform variables ------------------------------------

uniform bool isAnimated = false;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
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

	vec4 worldPosition = model * totalLocalPos;
	vec4 viewPosition = view * worldPosition;
	vec4 clipPosition = projection * viewPosition;

	gl_Position = clipPosition;
	vClipPosition = clipPosition;
}
