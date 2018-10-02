//
// Created by erick on 9/29/18.
//

#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(AnimatedVertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices){
    AnimatedIndexedModel model;

    for (unsigned int i = 0; i < numVertices ; i++){
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
        model.color.push_back(*vertices[i].GetColor());
        model.jointIDs.push_back(vertices[i].getJointIDs());
        model.jointWeights.push_back(vertices[i].getJointWeights());
    }

    for (unsigned int i = 0; i < numIndices ; i++){
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

AnimatedMesh::AnimatedMesh(std::vector<AnimatedVertex> &vertices, unsigned int numVertices, std::vector<GLuint> &indices, unsigned int numIndices){
    AnimatedIndexedModel model;

    for (unsigned int i = 0; i < numVertices ; i++){
        model.positions.push_back(*vertices[i].GetPos());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
        model.color.push_back(*vertices[i].GetColor());
        model.jointIDs.push_back(vertices[i].getJointIDs());
        model.jointWeights.push_back(vertices[i].getJointWeights());
    }

    for (unsigned int i = 0; i < numIndices ; i++){
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);
}

void AnimatedMesh::InitMesh(const AnimatedIndexedModel &model) {

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

        //Color data
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[COLOR_VB]);
            glBufferData(GL_ARRAY_BUFFER,model.color.size() * sizeof(model.color[0]),&model.color[0],GL_STATIC_DRAW);
            glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(3);

//TODO: allow suppoert for more than 3 joints
        //Joint IDS
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[JOINT_IDS_VB]);
            glBufferData(GL_ARRAY_BUFFER,model.jointIDs.size() * model.jointIDs[0].size(),&model.jointIDs[0],GL_STATIC_DRAW);
            glVertexAttribPointer(4,MAX_JOINTS_PER_VERTEX,GL_INT,GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(4);

        //Joint Weights
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[JOINT_WEIGHTS_VB]);
            glBufferData(GL_ARRAY_BUFFER,model.jointWeights.size() * model.jointWeights[0].size(),&model.jointWeights[0],GL_STATIC_DRAW);
            glVertexAttribPointer(5,MAX_JOINTS_PER_VERTEX,GL_FLOAT,GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(5);

        //Index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,m_vertexArrayBuffers[INDEX_VB]);  // Set as element array buffer because it references data from another array buffer.
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]),&model.indices[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
}


