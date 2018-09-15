//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUIENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_GUIENTITY_H

#include "../../Rendering/GUI/GUIMesh.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../../Rendering/GUI/GUIMaterial.h"
#include "../../Rendering/RenderingEngine.h"

class GUIEntity {
public:
    GUIEntity();

    GUIEntity(Transform &transform, GUIMaterial &material);

    void InitMesh();

    virtual ~GUIEntity();

    void ProcessInput(Input* input, float delta);

    void Update(float delta);

    void Render(RenderingEngine *engine) const;

    GUIEntity* AddChild(GUIEntity* child);

    GUIEntity* AddComponent(EntityComponent<GUIEntity,RenderingEngine>* component);

    GUIMesh& getGUIMesh() { return m_GUI_mesh; }

    void setGUIMesh(GUIMesh& m_GUIMesh) { GUIEntity::m_GUI_mesh = m_GUIMesh; }

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& m_transform) { GUIEntity::m_transform = m_transform; }

    GUIMaterial& getMaterial() { return m_material; }

    void setMaterial(GUIMaterial& m_material) { GUIEntity::m_material = m_material; }

    std::vector<GUIEntity *> &getChildren();

protected:
    std::vector<GUIEntity*> m_children;
    std::vector<EntityComponent<GUIEntity,RenderingEngine>*> m_components;

    GUIMesh m_GUI_mesh;
    GUIMaterial m_material;
    Transform m_transform;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIENTITY_H
