#version 400

//Input variables ------------------------------------------

in vec3 vTexCoord;

// ---------------------------------------------------------

//output variables ------------------------------------------

out vec4 colour;

// ----------------------------------------------------------

//uniform variables -----------------------------------------

uniform samplerCube skybox1;
uniform samplerCube skybox2;
uniform float blendFactor;

uniform vec4 fogColor;
uniform float fogLowerLimit;
uniform float fogUpperLimit;


// -----------------------------------------------------------

void main(){
	vec4 texture1 = texture(skybox1, vTexCoord);
	vec4 texture2 = texture(skybox2, vTexCoord);
	vec4 finalColour = mix(texture1, texture2, blendFactor);

	if(fogLowerLimit != 0 && fogUpperLimit != 0){ //Some fog effect to be shown
        float factor = (vTexCoord.y - fogLowerLimit) / (fogUpperLimit - fogLowerLimit);
        factor = clamp(factor,0.0,1.0);
        colour = mix(fogColor, finalColour,factor);
    }else{
        colour = finalColour;
	}
}