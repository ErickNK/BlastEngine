#version 400


//Input variables ------------------------------------------

in vec2 vTexCoord;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//uniform variables -----------------------------------------

uniform sampler2D gui_texture;

// -----------------------------------------------------------

void main(){

	colour = texture(gui_texture,vTexCoord);

}