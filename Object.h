#include <utility>

#ifndef MORDEROPENGLUDEMYTUTORIAL_OBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_OBJECT_H


#include <vector>
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
class Object {
public:
    Object() = default;

    Object(Mesh *mesh,Transform *transform, std::vector<Texture*> &textures):
    m_mesh(mesh), m_transform(transform), m_textures(textures){}

    Mesh *getMesh() { return m_mesh; }

    void setMesh(Mesh *m_mesh) { Object::m_mesh = m_mesh; }

    Transform *getTransform() { return m_transform; }

    void setTransform( Transform *m_transform) { Object::m_transform = m_transform; }

    std::vector<Texture*> &getTexture()  { return m_textures; }

    void setTexture(std::vector<Texture*> &m_textures) { Object::m_textures = m_textures; }

private:
    Mesh *m_mesh;

    Transform *m_transform;

    std::vector<Texture*> m_textures;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_OBJECT_H
