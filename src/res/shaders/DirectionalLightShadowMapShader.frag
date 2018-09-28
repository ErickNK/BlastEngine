#version 400

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

void main(){

    /**
     * MAIN fragment colouring
     * */
    colour = vec4(gl_FragCoord.z);
}