#version 440 core

#include "constants.vert"

/**
 *  Instanced geometry shader that renders input geometry to MAX_LIGHTS_PER_DRAW output layers.
 *  Used to render the light space position of objects in the scene according to multiple lights
 *  into textures in a texture array.
 * */

//uniform variables -----------------------------------------

uniform mat4 lightSpace[MAX_LIGHTS_PER_DRAW];

// -----------------------------------------------------------

//Input variables ------------------------------------------

layout(location = 0) in vec2 vTexCrd[];
layout(location = 1) in vec3 vNorm[];
layout(location = 2) in vec3 vFragPs[];
layout(location = 3) in vec4 vColor[];

/**
 * Input of world positions for all the vertices of the primitive
 * being received from the vertex shader. Therefore it is an array
 * because we are having 3 vertices(triangle) per call to the geometry shader.*/
layout(location = 4) in vec4 vWorldPosition[];

in gl_PerVertex{
    vec4 gl_Position;
    float gl_ClipDistance[MAX_CLIP_PLANES];
}gl_in[];

/**
 *
 * State that we will be getting triangles from the vertex shader
 * */
layout(triangles , invocations = MAX_LIGHTS_PER_DRAW) in;

// -----------------------------------------------------------

//output variables ------------------------------------------

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec3 vFragPos;
layout(location = 3) out vec4 vCol;

layout(location = 4) out vec4 vlightSpacePosition;

out gl_PerVertex{
    vec4 gl_Position;
    float gl_ClipDistance[MAX_CLIP_PLANES];
};

/**
 * State that our output will be triangle strips instead of triangles.
 * This allows us to be outputting the same thing as triangles.
 * */
layout(triangle_strip , max_vertices = 3) out;

// -----------------------------------------------------------

void main() {
    for ( int i = 0; i < 3; ++i) { //For all the vertices.

        //Pass on position without any change
        gl_Position = gl_in[i].gl_Position;
        vTexCoord = vTexCrd[i];
        vNormal = vNorm[i];
        vFragPos = vFragPs[i];
        vCol = vColor[i];

        //Get light space position.
        vlightSpacePosition = lightSpace[gl_InvocationID] * vWorldPosition[i];

        //Set texture to output to.
        gl_Layer = gl_InvocationID;

        EmitVertex();
    }
    EndPrimitive();
}