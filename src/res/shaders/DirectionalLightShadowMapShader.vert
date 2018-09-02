#version 330 core

//Attribute Pointers -----------------------------------

layout (location = 0) in vec3 position;

//------------------------------------------------------

//Uniform variables ------------------------------------

uniform mat4 model;
uniform mat4 directionalLightSpace;

//------------------------------------------------------

void main(){
	gl_Position = directionalLightSpace * model * vec4(position, 1.0);
}
