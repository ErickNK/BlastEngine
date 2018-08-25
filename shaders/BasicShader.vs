#version 330

//Attribute Pointers
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

//Output variables
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;

//Uniform variables
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

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
    vNormal = (model * vec4(-normal, 0.0)).xyz;
//    vNormal = mat3(transpose(inverse(model))) * normal; //TODO: normals are getting inversed

    /**
     * We need the world position of a vertex/Fragment. This is the position after transformation
     * has been applied only. The positions of other fragments will be interpolated as values are
     * sent to the fragment shader.
     *
     * We apply swizzling (vec4).xyz to get a vec3.
     * */
    vFragPos = (model * vec4(position, 1.0)).xyz;
}