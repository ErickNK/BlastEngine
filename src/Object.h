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

    Object(Mesh &mesh,Transform &transform, Material &material):
    m_mesh(mesh), m_transform(transform),m_material(material){}

    Mesh &getMesh() { return m_mesh; }

    void setMesh(Mesh &m_mesh) { Object::m_mesh = m_mesh; }

    Transform &getTransform() { return m_transform; }

    void setTransform( Transform &m_transform) { Object::m_transform = m_transform; }

    Material &getMaterial() { return m_material; }

    void setMaterial(Material &m_material) { Object::m_material = m_material; }

private:
    Mesh m_mesh;

    Material m_material;

    Transform m_transform;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_OBJECT_H
