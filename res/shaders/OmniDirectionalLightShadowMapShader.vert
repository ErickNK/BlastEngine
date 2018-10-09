#version 400

//Attribute Pointers -----------------------------------

layout (location = 0) in vec3 position;

//------------------------------------------------------

//Uniform variables ------------------------------------

uniform mat4 model;

//------------------------------------------------------

void main(){
    gl_Position = model * vec4(position, 1.0);
}
