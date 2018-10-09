#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out float vVisibility;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform float fogDensity;
uniform float fogGradient;


//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    gl_Position = projection * view * model * vec4(position, 1.0);

    /**
     * Get position of a vertex in relation to the camera
     * */
    vec4 viewSpace = view * model * vec4(position,1.0);

    float viewSpaceDistance = length(viewSpace.xyz);

    vVisibility = clamp( exp( -pow( (viewSpaceDistance * fogDensity), fogGradient) ), 0.0 , 1.0 );
}