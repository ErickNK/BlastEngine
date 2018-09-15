#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec3 vTexCoord;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    gl_Position = projection * view * model * vec4(position, 1.0);

	vTexCoord = position;
}