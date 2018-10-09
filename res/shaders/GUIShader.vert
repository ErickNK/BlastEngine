#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec2 position;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec2 vTexCoord;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//---------------------------------------------------------

void main(){

	gl_Position = /*projection * view **/ model * vec4(position, 0.0, 1.0);

	/**
	 * Converts the coordinate system to start from the top-left as (0,0)
	 * to the bottom right as (1,1)
	 * */
    vTexCoord = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0);
}