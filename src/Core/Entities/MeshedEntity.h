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
#include "../Components/EntityComponent.h"
#include "Entity.h"

class MeshedEntity : public Entity {
public:
    MeshedEntity() = default;

    MeshedEntity(Mesh &mesh, Transform &transform, Material &material);

    virtual ~MeshedEntity();

    void ProcessInputAll(Input* input, float delta);

    void UpdateAll(float delta);

    void RenderAll(Shader* shader) const;

    MeshedEntity* AddChild(MeshedEntity* child);

    MeshedEntity* AddComponent(EntityComponent<MeshedEntity>* component);

    std::vector<EntityComponent<MeshedEntity> *> &getComponents();

//    std::vector<MeshedEntity*> GetAllAttached();

    Mesh& getMesh() { return m_mesh; }

    void setMesh(Mesh& m_mesh) { MeshedEntity::m_mesh = m_mesh; }

    Material& getMaterial() { return m_material; }

    void setMaterial(Material& m_material) { MeshedEntity::m_material = m_material; }

protected:
    std::vector<MeshedEntity*> m_children;
    std::vector<EntityComponent<MeshedEntity>*> m_components;

    Mesh m_mesh;
    Material m_material;

    void ProcessInput(Input* input, float delta) override;

    void Update(float delta) override;

    void Render(Shader* shader) const;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHEDOBJECT_H
