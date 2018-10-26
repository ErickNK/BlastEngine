#version 330 core


//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec3 vNormal;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;

//---------------------------------------------------------

void main()
{
    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    gl_Position = projection * view * model * vec4(position, 1.0);

//    mat3 normalMatrix = mat3(transpose(inverse(view * model)));

//    vNormal = normalize(vec3(projection * vec4(normalMatrix * normal, 0.0)));

    vNormal = normalMatrix * actualNormal;
}