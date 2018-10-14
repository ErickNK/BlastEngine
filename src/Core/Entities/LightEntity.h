//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H


#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../Components/EntityComponent.h"
#include "Entity.h"
#include "../../Rendering/Lighting/Shadow.h"

class ShadowRendererComponent;
class CoreEngine;
class RenderingEngine;
class Scene;
class Light;

class LightEntity: public Entity {
public:

    explicit LightEntity(LightType lightType);

    LightEntity(LightType lightType,glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat shadowWidth, GLfloat shadowHeight);

    virtual ~LightEntity();

    void ProcessInput(Input* input, float delta) override;

    void Update(double time, float delta) override;

    void RenderLight(RenderingEngine* engine) const;

    void RenderShadow(RenderingEngine* engine) const;

    LightEntity* AddComponent(EntityComponent<LightEntity>* component);

    LightEntity* AddShadowComponent(ShadowRendererComponent* component);

    virtual void UseLight(Shader* shader){}

    FrameBufferObject GetShadowMapFBO() { return m_shadow.shadow_map_fbo; }

    Shadow& GetShadow() { return m_shadow; }

    GLuint GetShadowMapTexture() { return m_shadow.shadow_map_texture; }

    const glm::vec3 &getColor() const;

    GLfloat getAmbientIntensity() const;

    LightType getType() const;

    bool isCellShadingOn() const;

    void setAllowCellShading(bool m_allow_cell_shading);

    int getId() const;

    void setId(int id);

protected:
    std::vector<EntityComponent<LightEntity>*> m_light_components;

    std::vector<ShadowRendererComponent*> m_shadow_components;

    glm::vec3 color;

    GLfloat ambientIntensity;

    GLfloat diffuseIntensity;

    int m_id;

    LightType m_type;

    Shadow m_shadow;

    //TODO improve cell shading
    bool m_allow_cell_shading = false;

    int m_cell_shading_level = 2;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
