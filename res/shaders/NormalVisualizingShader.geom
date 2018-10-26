#version 330 core

#include "constants.vert"
//Input variables ------------------------------------------

layout (triangles) in;

in vec3 vNormal[];

// -----------------------------------------------------------

//output variables -------------------------------------------

layout (line_strip, max_vertices = 6) out;

//out gl_PerVertex{
//        vec4 gl_Position;
//        float gl_ClipDistance[MAX_CLIP_PLANES];
//};

// -----------------------------------------------------------

const float MAGNITUDE = 0.4;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();

    gl_Position = gl_in[index].gl_Position + vec4(vNormal[index], 0.0) * MAGNITUDE;
    EmitVertex();

    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}