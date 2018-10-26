#version 440 core

#include "constants.vert"

/**
 *  instanced geometry shader that renders input geometry to MAX_LIGHTS_PER_DRAW output layers.
 * */

//uniform variables -----------------------------------------

uniform mat4 lightSpace[MAX_LIGHTS_PER_DRAW];

// -----------------------------------------------------------

//Input variables ------------------------------------------

layout(location = 0) in vec4 vWorldPosition[];

in gl_PerVertex{
        vec4 gl_Position;
        float gl_ClipDistance[MAX_CLIP_PLANES];
}gl_in[];

layout(triangles , invocations = MAX_LIGHTS_PER_DRAW) in;

// -----------------------------------------------------------

//output variables ------------------------------------------

layout(triangle_strip , max_vertices = 3) out;

layout(location = 0) out vec4 vlightSpacePosition;

out gl_PerVertex{
        vec4 gl_Position;
        float gl_ClipDistance[MAX_CLIP_PLANES];
};

// -----------------------------------------------------------

void main() {
    for ( int i = 0 ; i < gl_in.length(); ++i) {
        vec4 lightSpacePosition = lightSpace[gl_InvocationID] * vWorldPosition[i];

        //Set position of vertex according to light space
        gl_Position = lightSpacePosition;

        //Send the light space position to fragment shader
        vlightSpacePosition = lightSpace[gl_InvocationID] * vWorldPosition[i];

        //Set texture to output to.
        gl_Layer = gl_InvocationID;

        EmitVertex();
    }
    EndPrimitive();
}