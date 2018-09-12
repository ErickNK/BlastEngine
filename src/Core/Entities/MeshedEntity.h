//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MESHEDOBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_MESHEDOBJECT_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../../Rendering/Camera/Camera.h"
#include "../../Rendering/Mesh.h"
#include "../../Rendering/Material.h"
#include "../Components/MeshedComponent.h"

class MeshedEntity {
public:
    MeshedEntity() = default;

    MeshedEntity(Mesh &mesh, Transform &transform, Material &material);

    virtual ~MeshedEntity();

    void ProcessInputAll(const Input* input, float delta);

    void UpdateAll(float delta);

    void RenderAll(Shader* shader) const;

    MeshedEntity* AddChild(MeshedEntity* child);

    MeshedEntity* AddComponent(MeshedComponent* component);

//    std::vector<MeshedEntity*> GetAllAttached();

    Mesh& getMesh() { return m_mesh; }

    void setMesh(Mesh& m_mesh) { MeshedEntity::m_mesh = m_mesh; }

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& m_transform) { MeshedEntity::m_transform = m_transform; }

    Material& getMaterial() { return m_material; }

    void setMaterial(Material& m_material) { MeshedEntity::m_material = m_material; }

protected:
    std::vector<MeshedEntity*> m_children;
    std::vector<MeshedComponent*> m_components;

    Mesh m_mesh;
    Material m_material;
    Transform m_transform;

    void ProcessInput(const Input* input, float delta);

    void Update(float delta);

    void Render(Shader* shader) const;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHEDOBJECT_H
