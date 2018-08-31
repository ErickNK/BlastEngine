//
// Created by erick on 8/12/18.
//

#include "Mesh.h"
#include "obj_loader.h"
#include <vector>

Mesh::Mesh(const std::string& filename){
    IndexedModel model = OBJModel(filename).ToIndexedModel();

    InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices,
        unsigned int* indices, unsigned int numIndices) {

    IndexedModel model;

    for (unsigned int i = 0; i < numVertices ; i++){
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }

    for (unsigned int i = 0; i < numIndices ; i++){
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

Mesh::Mesh(std::vector<Vertex>& vertices, unsigned int numVertices, 
	std::vector<GLuint>& indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++) {
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++) {
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);
}

Mesh::~Mesh() {
    //glDeleteVertexArrays(1,&m_vertexArrayObject);
}

void Mesh::Draw() {

    glBindVertexArray(m_vertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);

			glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr); //Draw from index buffer

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel &model) {

    m_drawCount = static_cast<unsigned int>(model.indices.size());

    //Generate the VAO
    glGenVertexArrays(1,&m_vertexArrayObject);
    //Start editing vertex array object
    glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //Request buffers

        //Position data
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]); //Bind buffers for manipulation as array buffer
            glBufferData(GL_ARRAY_BUFFER,model.positions.size() * sizeof(model.positions[0]),&model.positions[0],GL_STATIC_DRAW); //Add data
            // Define a pointer to allow shader to access this buffer's vertex data.
            glVertexAttribPointer(
                    0, // Location in the shader.
                    3, // Size of each value passed in. Because we are passing 3 values (x,y,z) it's 3.
                    GL_FLOAT, // Type of the values
                    GL_FALSE, // No normalization
                    0, /* If you have multiple data in the main data-set, e.g (color data mixed with position data)
                               you can define number of data units to skip in order to get to the next data units of same data type. */
                    nullptr // offset to start from.
            );
            glEnableVertexAttribArray(0);// Enable attribute pointer at location 0.

        //Texture data
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[TEXCOORD_VB]);
            glBufferData(GL_ARRAY_BUFFER,model.texCoords.size() * sizeof(model.texCoords[0]),&model.texCoords[0],GL_STATIC_DRAW);
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);

        //Normal data
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[NORMAL_VB]);
            glBufferData(GL_ARRAY_BUFFER,model.normals.size() * sizeof(model.normals[0]),&model.normals[0],GL_STATIC_DRAW);
            glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(2);

        //Index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,m_vertexArrayBuffers[INDEX_VB]);  // Set as element array buffer because it references data from another array buffer.
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]),&model.indices[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
}
