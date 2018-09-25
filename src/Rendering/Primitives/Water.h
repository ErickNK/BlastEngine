//
// Created by erick on 9/22/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_WATER_H
#define MORDEROPENGLUDEMYTUTORIAL_WATER_H


#include "../../Core/Entities/MeshedEntity.h"
#include "../PostProcessing/FrameBufferObject.h"

class RenderingEngine;
class WaterRendererComponent;

class WaterMaterial: public Material{
public:

    WaterMaterial(GLfloat d, GLfloat d1, std::vector<Texture *> vector);

    void UseMaterial(Shader *shader) override;

    GLfloat fresnelIntensity = 1.0f;

};

class Water : public MeshedEntity {
public:

    Water() = default;

    Water(int gridX, int gridZ, int gridY);

    Water(int gridX, int gridZ, int gridY, std::map<TextureTypeEnum, std::string> textures);

    void setTILE_SIZE(float TILE_SIZE);

    void Update(double time, float delta) override;

public:
    void RenderWater(RenderingEngine *engine);

    const FrameBufferObject &getReflectionFBO() const;

    const FrameBufferObject &getRefractionFBO() const;

    int getReflectionTexture() const {
        return reflectionTexture;
    }

    int getReflectionDepthBuffer() const {
        return reflectionDepthBuffer;
    }

    int getRefractionTexture() const {
        return refractionTexture;
    }

    int getRefractionDepthTexture() const {
        return refractionDepthTexture;
    }

    float getHeight();

    GLfloat wave_tiling = 6.0f;
    GLfloat wave_strength = 0.2f;
    GLfloat wave_speed = 0.03f;
    GLfloat moveFactor = 0.0f;
private:
    float TILE_SIZE = 400, x = 0, z = 0, height = 0;

    std::map<TextureTypeEnum, std::string> m_textureLocations;

    GLuint REFLECTION_WIDTH = 320;
    GLuint REFLECTION_HEIGHT = 180;
    GLuint REFRACTION_WIDTH = 1280;
    GLuint REFRACTION_HEIGHT = 720;

    FrameBufferObject reflection_fbo;
    FrameBufferObject refraction_fbo;

    WaterRendererComponent* waterRendererComponent;

    GLuint reflectionTexture, reflectionDepthBuffer, refractionTexture, refractionDepthTexture;

    void InitWater();

    void InitFBOs();

    void AddComponents();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WATER_H
