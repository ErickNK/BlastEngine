#version 400

//Input variables ------------------------------------------

in float vVisibility;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//Uniforms variables ------------------------------------------

uniform vec4 fogColor;

// ----------------------------------------------------------

void main(){

    /**
     * MAIN fragment colouring
     * */
    colour = mix(fogColor,vec4(0,0,0,0),vVisibility);
}