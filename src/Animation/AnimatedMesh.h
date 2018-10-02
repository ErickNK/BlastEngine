//
// Created by erick on 9/29/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDMESH_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDMESH_H


#include "../Rendering/Mesh.h"

class AnimatedIndexedModel : public IndexedModel{
public:
    std::vector<std::vector<int>> jointIDs;
    std::vector<std::vector<float>> jointWeights;
};


class AnimatedVertex: public Vertex{
public:
    AnimatedVertex(): Vertex() {

        for (int i = 0; i < MAX_JOINTS_PER_VERTEX; ++i) {
            this->jointIDs.push_back(-1);
            this->jointWeights.push_back(-1.0f);
        }
    }

    explicit AnimatedVertex(
            const glm::vec3& pos,
            const glm::vec2& texCoord = glm::vec2(0, 0),
            const glm::vec3& normal = glm::vec3(0,0,0),
            const glm::vec3& tangent = glm::vec3(0,0,0),
            const glm::vec4& color = glm::vec4(1,1,1,1),
            const std::vector<int> &jointIDs = {},
            const std::vector<float> &jointWeights = {}
    ): Vertex(pos,texCoord,normal,tangent,color){

        for (int i = 0; i < MAX_JOINTS_PER_VERTEX; ++i) {
            this->jointIDs.push_back(-1);
            this->jointWeights.push_back(-1.0f);
        }

    }

    std::vector<int> getJointIDs()  {
        return jointIDs;
    }

    std::vector<float> getJointWeights() {
        return jointWeights;
    }

    void setJointID(int position, int id) {
        AnimatedVertex::jointIDs[position] = id;
    }

    void setJointWeight(int position, float value) {
        AnimatedVertex::jointWeights[position] = value;
    }

    int& getWeightCount() {
        return m_weight_count;
    }

protected:
    int m_weight_count = 0;
    std::vector<int> jointIDs; //ids of the joints/bones that affect this vertex.
    std::vector<float> jointWeights; //ids of the joints/bones that affect this vertex.
};

class AnimatedMesh : public Mesh{
public:
    AnimatedMesh(): Mesh(){}

    AnimatedMesh(AnimatedVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    AnimatedMesh(std::vector<AnimatedVertex>& vertices, unsigned int numVertices, std::vector<GLuint>& indices, unsigned int numIndices);

protected:
    void InitMesh(const AnimatedIndexedModel &model);

};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDMESH_H
