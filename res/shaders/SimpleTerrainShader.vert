#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec2 vTexCoord;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    gl_Position = projection * view * model * vec4(position, 1.0);

    /**
     * Directly pass the texture coordinates
     * */
    vTexCoord = texCoord;
}