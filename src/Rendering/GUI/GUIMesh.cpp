//
// Created by erick on 9/15/18.
//

#include "GUIMesh.h"

GUIMesh::GUIMesh(std::vector<glm::vec2> pos, unsigned int numVertices) {

    for (unsigned int i = 0; i < numVertices ; i++){
        m_drawCount++;
        positions.push_back(pos[i]);
    }

    InitGUIMesh();
}

void GUIMesh::Bind() const {
    glBindVertexArray(m_vertexArrayObject);
}

void GUIMesh::Draw() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount); //Draw
}

void GUIMesh::UnBind() const {
    glBindVertexArray(0);
}

void GUIMesh::InitGUIMesh() {



    //Generate the VAO
    glGenVertexArrays(1,&m_vertexArrayObject);
    //Start editing vertex array object
    glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(1, m_vertexArrayBuffers); //Request buffers

        //Position data
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]); //Bind buffers for manipulation as array buffer
            glBufferData(GL_ARRAY_BUFFER,positions.size() * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW); //Add data
            // Define a pointer to allow shader to access this buffer's vertex data.
            glVertexAttribPointer(
                    0, // Location in the shader.
                    2, // Size of each value passed in. Because we are passing 3 values (x,y) it's 2.
                    GL_FLOAT, // Type of the values
                    GL_FALSE, // No normalization
                    0, /* If you have multiple data in the main data-set, e.g (color data mixed with position data)
                                       you can define number of data units to skip in order to get to the next data units of same data type. */
                    nullptr // offset to start from.
            );
            glEnableVertexAttribArray(0);// Enable attribute pointer at location 0.

    glBindVertexArray(0);
}



