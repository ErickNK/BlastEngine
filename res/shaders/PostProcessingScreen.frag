#version 400


//Input variables ------------------------------------------

in vec2 vTexCoord;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//uniform variables -----------------------------------------

uniform sampler2D screen_texture;

// -----------------------------------------------------------

void main(){

    colour = texture(screen_texture,vTexCoord);

}