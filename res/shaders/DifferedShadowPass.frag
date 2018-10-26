#version 440 core


//Input variables ------------------------------------------

layout(location = 0) in vec4 vlightSpacePosition;

// ---------------------------------------------------------

//output variables ------------------------------------------

layout (location = 0) out vec4 out_light_space_position;

// ----------------------------------------------------------


void main(){
    out_light_space_position = vlightSpacePosition;
}