#include <utility>

#ifndef MORDEROPENGLUDEMYTUTORIAL_OBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_OBJECT_H


#include <vector>
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Material.h"

class Object {
public:
    Object() = default;

    Object(Mesh *mesh,Transform *transform, std::vector<Texture*> &textures, Material *material):
    m_mesh(mesh), m_transform(transform), m_textures(textures),m_material(material){}

    Mesh *getMesh() { return m_mesh; }

    void setMesh(Mesh *m_mesh) { Object::m_mesh = m_mesh; }

    Transform *getTransform() { return m_transform; }

    void setTransform( Transform *m_transform) { Object::m_transform = m_transform; }

    std::vector<Texture*> &getTexture()  { return m_textures; }

    void setTexture(std::vector<Texture*> &m_textures) { Object::m_textures = m_textures; }

    Material *getMaterial() { return m_material; }

    void setMaterial(Material *m_material) { Object::m_material = m_material; }

private:
    Mesh *m_mesh;

    Material *m_material;

    Transform *m_transform;

    std::vector<Texture*> m_textures;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_OBJECT_H
