#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;
out vec4 vCol;

/* Position of the fragment relative to the light */
out vec4 vDirectionalLightSpacePosition;

//---------------------------------------------------------

//Lighting ------------------------------------------------

uniform mat4 directionalLightSpace;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;

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
    vTexCoord = texCoord * 40.0;
    vCol = color;

    /**
     * The normal is just a direction from the vertex. The position of the vertex is
     * the origin of the normal. If we rotate the vertex the direction might change, if
     * we scale the vertex the direction might also change, but moving the vertex will not
     * change the direction. We multiply with model to apply transformation and disable translation(moving).
     *
     * We inverse and transpose to avoid scaling skewing our normal direction, thus accounting for
     * non-uniform scaling. We then convert to mat3 to disable translation. The mat3 will multiplication
     * will return a vec3 which is what we want.
     * */
    vNormal = normalMatrix * normal;

    /**
     * We need the world position of a vertex/Fragment. This is the position after transformation
     * has been applied only. The positions of other fragments will be interpolated as values are
     * sent to the fragment shader.
     *
     * We apply swizzling (vec4).xyz to get a vec3.
     * */
    vFragPos = (model * vec4(position, 1.0)).xyz;

    /**
    * We need the world position of a vertex/Fragment relative to the lights point of view
    *(thus its lightSpaceTransform).
    *
    * */
    vDirectionalLightSpacePosition = directionalLightSpace * model * vec4(position, 1.0);
}