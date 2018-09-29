#version 400

//Attribute Pointers -----------------------------------

layout (location = 0) in vec3 position;

//------------------------------------------------------

//Uniform variables ------------------------------------

out vec4 vClipPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//------------------------------------------------------

void main(){
	vec4 worldPosition = model * vec4(position, 1.0);
	vec4 viewPosition = view * worldPosition;
	vec4 clipPosition = projection * viewPosition;

	gl_Position = clipPosition;
	vClipPosition = clipPosition;
}
