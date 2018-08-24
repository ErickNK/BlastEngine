//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_UTIL_H
#define MORDEROPENGLUDEMYTUTORIAL_UTIL_H

#include <cstdlib>
#include "Mesh.h"

void CalAverageNormals(Vertex* vertices, unsigned int numVertices,
                       unsigned int* indices, unsigned int numIndices,
                       unsigned int numFaces){

    unsigned int numVerticesPerFace = numIndices/numFaces; //How much to skip when getting the indices per face.

    for(size_t i = 0; i < numIndices; i += numVerticesPerFace){ //For each face

        //Get the vertices per this face
        Vertex* verticesPerFace[numVerticesPerFace];
        for(size_t ii = 0; ii < numVerticesPerFace; ii++) verticesPerFace[ii] = &vertices[indices[i + ii]];

        //Get a perpendicular line from two vertices derived from getting difference of 2 vertices of the face
        glm::vec3 v1(
                verticesPerFace[1]->GetPos()->x - verticesPerFace[0]->GetPos()->x,
                verticesPerFace[1]->GetPos()->y - verticesPerFace[0]->GetPos()->y,
                verticesPerFace[1]->GetPos()->z - verticesPerFace[0]->GetPos()->z
        );
        glm::vec3 v2(
                verticesPerFace[2]->GetPos()->x - verticesPerFace[0]->GetPos()->x,
                verticesPerFace[2]->GetPos()->y - verticesPerFace[0]->GetPos()->y,
                verticesPerFace[2]->GetPos()->z - verticesPerFace[0]->GetPos()->z
        );
        glm::vec3 normal = glm::normalize(glm::cross(v1,v2));

        //Place the normals in the vertices for this face
        for(size_t ii = 0; ii < numVerticesPerFace; ii++){ //For each vertex of this face
            verticesPerFace[ii]->GetNormal()->x += normal.x;
            verticesPerFace[ii]->GetNormal()->y += normal.y;
            verticesPerFace[ii]->GetNormal()->z += normal.z;
        }
    }

    //Normalize all the normals
    for(size_t i = 0; i < numVertices; i++){
        vertices[i].SetNormal(glm::normalize(*vertices[i].GetNormal()));
    }
}

#endif //MORDEROPENGLUDEMYTUTORIAL_UTIL_H
