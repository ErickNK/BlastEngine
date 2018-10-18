#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 3) in vec4 color;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec4 vClipSpace;
out vec2 vTexCoord;
out vec3 vToCameraVector;
out vec3 vFragPos;
out vec4 vCol;
//out vec3 vFromLightVector;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform float waveTiling;
//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    vec4 worldPosition = model * vec4(position, 1.0);
    vec4 viewPosition = view * worldPosition;
    vec4 clipPosition = projection * viewPosition;

    gl_Position = clipPosition;

    /**
     * Directly pass the texture coordinates
     * */
    vClipSpace = clipPosition;

    vTexCoord = vec2((position.x * 0.01)/2.0 + 0.5, (position.z * 0.01)/2.0 + 0.5) * waveTiling;

    vToCameraVector = cameraPosition - worldPosition.xyz;

//    vFromLightVector = worldPosition.xyz - lightPosition;

/**
     * We need the world position of a vertex/Fragment. This is the position after transformation
     * has been applied only. The positions of other fragments will be interpolated as values are
     * sent to the fragment shader.
     *
     * We apply swizzling (vec4).xyz to get a vec3.
     * */
    vFragPos = (model * vec4(position, 1.0)).xyz;
    vCol = color;
}