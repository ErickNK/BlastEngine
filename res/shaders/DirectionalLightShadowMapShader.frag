#version 400

//output variables ------------------------------------------

layout (location = 0) out vec4 colour;

// ----------------------------------------------------------

void main(){

    /**
     * MAIN fragment colouring
     * */
    colour = vec4(gl_FragCoord.z,(gl_FragCoord.z * 1), 0.0f, 0.0f);
}