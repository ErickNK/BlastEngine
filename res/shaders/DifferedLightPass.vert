#version 440 core

#include "constants.vert"

//Attribute Pointers --------------------------------------

layout (location = 0) in vec2 position;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

layout (location = 0) out vec2 vTexCoord;

//---------------------------------------------------------

//Uniforms ------------------------------------------------

uniform mat4 model;

//---------------------------------------------------------

void main(){

    vec4 worldPosition = model * vec4(position, 0.0, 1.0);
    gl_Position = worldPosition;

    /**
     * Converts the coordinate system to start from the top-left as (0,0)
     * to the bottom right as (1,1)
     * */
    vTexCoord = vec2((worldPosition.x + 1.0)/2.0, (worldPosition.y + 1.0)/2.0);
}