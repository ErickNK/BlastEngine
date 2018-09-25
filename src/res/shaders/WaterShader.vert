#version 400

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec4 vClipSpace;
out vec2 vTexCoord;
out vec3 vToCameraVector;
//out vec3 vFromLightVector;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform float waveTiling;
//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */
    vec4 worldPosition = model * vec4(position, 1.0);
    vec4 viewPosition = view * worldPosition;
    vec4 clipPosition = projection * viewPosition;

    gl_Position = clipPosition;

    /**
     * Directly pass the texture coordinates
     * */
    vClipSpace = clipPosition;

    vTexCoord = vec2((position.x * 0.01)/2.0 + 0.5, (position.z * 0.01)/2.0 + 0.5) * waveTiling;

    vToCameraVector = cameraPosition - worldPosition.xyz;

//    vFromLightVector = worldPosition.xyz - lightPosition;
}