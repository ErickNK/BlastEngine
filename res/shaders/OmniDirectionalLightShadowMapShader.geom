#version 400

//Geometry Shader --------------------------------------

layout (triangles) in;
layout (triangle_strips, max_vertices = 18) out;

//------------------------------------------------------

//Uniform variables ------------------------------------

uniform mat4 lightSpaces[6]; //projection * view of the light source, In all directions

//------------------------------------------------------

//output variables ------------------------------------------

out vec4 vFragPos;

// ----------------------------------------------------------

void main(){
    for(int face = 0; face < 6; face++){
        gl_Layer = face; //Specify which texture on cube to draw to.
        for(int i = 0; i < 3; i++){ //Loop through triangles coming in
            vFragPos = gl_in[i].gl_Position;
        }
    }
}
