#version 330

//Attribute Pointers
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

//Output variables
out vec4 vCol;
out vec2 vTexCoord;
out vec3 vNormal;

//Uniform variables
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main(){

    gl_Position = projection * view * model * vec4(position, 1.0);

    vCol = vec4(clamp(position, 0.0f, 1.0), 1.0f);

    vTexCoord = texCoord;
//    vNormal = (model * vec4(normal, 0.0)).xyz;
}