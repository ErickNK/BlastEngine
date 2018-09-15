//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUIMESH_H
#define MORDEROPENGLUDEMYTUTORIAL_GUIMESH_H


#include "../Mesh.h"

class GUIMesh : public Mesh{
public:
    GUIMesh() = default;

    GUIMesh(std::vector<glm::vec2> positions, unsigned int numVertices);

    void Draw() override;

    void InitGUIMesh();

    void Bind() const;

    void UnBind() const;

private:
    std::vector<glm::vec2> positions;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIMESH_H
