#version 330

//Input variables
in vec4 vCol;
in vec2 vTexCoord;
in vec3 vNormal;

//output variables
out vec4 colour;

//uniform variables
uniform sampler2D diffuse;

void main(){
   colour = texture2D(diffuse, vTexCoord);
//            * clamp(dot(-vec3(0,0,1), vNormal),0.0,1.0);
}