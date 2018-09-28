#include <utility>

//
// Created by erick on 9/22/18.
//

#include "Water.h"
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../../Core/Components/RenderingComponents/WaterRendererComponent.h"
#include "../GUI/GUIMesh.h"

Water::Water(int gridX, int gridZ, int gridY): MeshedEntity() {
    x = gridX * TILE_SIZE;
    z = gridZ * TILE_SIZE;
    height = gridY;
    InitFBOs();
    InitWater();
}
Water::Water(int gridX, int gridZ, int gridY, std::map<TextureTypeEnum, std::string> textures): MeshedEntity() {
    m_textureLocations = std::move(textures);
    x = gridX * TILE_SIZE;
    z = gridZ * TILE_SIZE;
    height = gridY;
    InitFBOs();
    InitWater();
}

void Water::InitWater() {
    //Load mesh
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture*> textures;

    vertices.emplace_back(glm::vec3(-1,0,-1) * TILE_SIZE,glm::vec2(),glm::vec3(0,1,0),glm::vec3(),glm::vec4(0,0,0,0));
    vertices.emplace_back(glm::vec3(-1,0,1) * TILE_SIZE,glm::vec2(),glm::vec3(0,1,0),glm::vec3(),glm::vec4(0,0,0,0));
    vertices.emplace_back(glm::vec3(1,0,1) * TILE_SIZE,glm::vec2(),glm::vec3(0,1,0),glm::vec3(),glm::vec4(0,0,0,0));
    vertices.emplace_back(glm::vec3(1,0,-1) * TILE_SIZE,glm::vec2(),glm::vec3(0,1,0),glm::vec3(),glm::vec4(0,0,0,0));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    m_mesh =  new Mesh(vertices, vertices.size(), indices, indices.size());

    for (auto const &x : m_textureLocations) {
        textures.push_back(new Texture(x.second, x.first));
    }
    textures.push_back(new Texture(reflection_fbo.GetTextures()[reflectionTexture],WATER_REFLECTION_TEXTURE));
    textures.push_back(new Texture(refraction_fbo.GetTextures()[refractionTexture],WATER_REFRACTION_TEXTURE));
    textures.push_back(new Texture(refraction_fbo.GetTextures()[refractionDepthTexture],WATER_REFRACTION_DEPTH_TEXTURE));
    m_material = new WaterMaterial(0.9, 30.0, textures);

    m_transform = Transform();
    m_transform.GetPos().x = x;
    m_transform.GetPos().z = z;
    m_transform.GetPos().y = height;
    m_transform.GetScale() * TILE_SIZE;

    AddComponents();
}

void Water::InitFBOs() {
    GLenum options[NUM_FBO_OPTIONS];

    options[TYPE] = GL_TEXTURE;
    options[TEXTURE_TYPE] = GL_TEXTURE_2D;
    options[INTERNAL_COMPONENT_FORMAT] = GL_RGB;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_RGB;
    options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT0;
    options[ENABLE_WRAP_FILTER] = GL_FALSE;
    options[ENABLE_OVERLAY_FILTER] = GL_FALSE;
    reflection_fbo.Generate(reflectionTexture, REFLECTION_WIDTH,REFLECTION_HEIGHT,options);

    options[TYPE] = GL_RENDERBUFFER;
    options[RENDER_BUFFER_TYPE] = GL_RENDERBUFFER;
    options[INTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
    options[ATTACHMENT_TYPE] = GL_DEPTH_ATTACHMENT;
    options[ENABLE_WRAP_FILTER] = GL_FALSE;
    options[ENABLE_OVERLAY_FILTER] = GL_FALSE;
    reflection_fbo.Generate(reflectionDepthBuffer, REFLECTION_WIDTH,REFLECTION_HEIGHT,options);

    options[TYPE] = GL_TEXTURE;
    options[TEXTURE_TYPE] = GL_TEXTURE_2D;
    options[INTERNAL_COMPONENT_FORMAT] = GL_RGB;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_RGB;
    options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT0;
    options[ENABLE_WRAP_FILTER] = GL_FALSE;
    options[ENABLE_OVERLAY_FILTER] = GL_FALSE;
    refraction_fbo.Generate(refractionTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT,options);

    options[TYPE] = GL_TEXTURE;
    options[TEXTURE_TYPE] = GL_TEXTURE_2D;
    options[INTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT32;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
    options[ATTACHMENT_TYPE] = GL_DEPTH_ATTACHMENT;
    options[ENABLE_WRAP_FILTER] = GL_FALSE;
    options[ENABLE_OVERLAY_FILTER] = GL_FALSE;
    refraction_fbo.Generate(refractionDepthTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT,options);

}

void Water::AddComponents(){
    //ADD COMPONENTS
    auto * renderer = new MeshedRendererComponent();
    this->AddComponent(renderer);

    this->waterRendererComponent = new WaterRendererComponent();
    this->waterRendererComponent->SetParent(this);
}

void Water::setTILE_SIZE(float TILE_SIZE) {
    Water::TILE_SIZE = TILE_SIZE;
}

void Water::RenderWater(RenderingEngine *engine) {
    if(allow_render) waterRendererComponent->RenderWater(engine);
}

const FrameBufferObject &Water::getReflectionFBO() const {
    return reflection_fbo;
}

const FrameBufferObject &Water::getRefractionFBO() const {
    return refraction_fbo;
}

float Water::getHeight() {
    return height;
}

void Water::Update(double time, float delta) {
    MeshedEntity::Update(time, delta);
    waterRendererComponent->Update(time, delta);
}

void WaterMaterial::UseMaterial(Shader *shader) {
    Material::UseMaterial(shader);

    for (unsigned int i = 0; i < textures.size(); i++) {
        int textureUnit = shader->getAvailableDrawingTextureUnit();
        switch (textures[i]->GetTextureType()) {
            case WATER_REFLECTION_TEXTURE: {
                shader->Uniform1i("material.reflectionTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case WATER_REFRACTION_TEXTURE: {
                shader->Uniform1i("material.refractionTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case WATER_REFRACTION_DEPTH_TEXTURE: {
                shader->Uniform1i("material.refractionDepthTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case DU_DV_MAP: {
                shader->Uniform1i("material.dudvMap", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case NORMAL_MAP: {
                shader->Uniform1i("material.normalMap", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }
        }
    }

    //Set Fresnel intensity
    shader->Uniform1f("material.fresnelIntensity",fresnelIntensity);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

WaterMaterial::WaterMaterial(GLfloat d, GLfloat d1, std::vector<Texture *> vector) : Material(d,d1,vector){}
