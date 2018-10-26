#include <utility>

//
// Created by erick on 10/10/18.
//

#include "DifferedScreen.h"
#include "../Shaders/PostProcessingScreenShader.h"
#include "../Shaders/DifferedShader.h"
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"

DifferedScreenMesh::DifferedScreenMesh(std::vector<glm::vec2> pos, unsigned int numVertices) {

    for (unsigned int i = 0; i < numVertices ; i++){
        m_drawCount++;
        positions.push_back(pos[i]);
    }

    InitDifferedScreenMesh();
}


void DifferedScreenMesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount); //Draw
    glBindVertexArray(0);

}

void DifferedScreenMesh::InitDifferedScreenMesh() {

    //Generate the VAO
    glGenVertexArrays(1,&m_vertexArrayObject);
    //Start editing vertex array object
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, m_vertexArrayBuffers); //Request buffers

    //Position data
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]); //Bind buffers for manipulation as array buffer
    glBufferData(GL_ARRAY_BUFFER,positions.size() * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW); //Add data
    // Define a pointer to allow shader to access this buffer's vertex data.
    glVertexAttribPointer(
            0, // Location in the shader.
            2, // Size of each value passed in. Because we are passing 3 values (x,y) it's 2.
            GL_FLOAT, // Type of the values
            GL_FALSE, // No normalization
            0, /* If you have multiple data in the main data-set, e.g (color data mixed with position data)
                                       you can define number of data units to skip in order to get to the next data units of same data type. */
            nullptr // offset to start from.
    );
    glEnableVertexAttribArray(0);// Enable attribute pointer at location 0.

    glBindVertexArray(0);
}

DifferedScreenMaterial::DifferedScreenMaterial() : Material() {}

DifferedScreenMaterial::DifferedScreenMaterial(std::vector<Texture*>& textures) : Material(0,0,textures){}

void DifferedScreenMaterial::UseMaterial(Shader *shader) {
    glCheckError();
    for (unsigned int i = 0; i < textures.size(); i++) {
        int textureUnit = shader->getAvailableDrawingTextureUnit();
        switch (textures[i]->GetTextureType()) {
            case POSITION_TEXTURE: {
                shader->Uniform1i("positionTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case NORMAL_MAP: {
                shader->Uniform1i("normalTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case DIFFUSE_TEXTURE: {
                shader->Uniform1i("diffuseTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case SPECULAR_TEXTURE: {
                shader->Uniform1i("specularTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case MATERIAL_TEXTURE: {
                shader->Uniform1i("materialTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case DEPTH_TEXTURE: {
                shader->Uniform1i("depthTexture", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case SHADOW_MAP_TEXTURE_ARRAY: {
                shader->Uniform1i("shadowMapTextureArray", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }

            case LIGHT_SPACE_POSITION_TEXTURE_ARRAY: {
                shader->Uniform1i("lightSpacePositionTextureArray", textureUnit);
                textures[i]->Bind(textureUnit);
                break;
            }
        }
    }

    glCheckError();
}

DifferedScreen::DifferedScreen() {
    std::vector<glm::vec2> positions;
    positions.emplace_back(-1,1);
    positions.emplace_back(-1,-1);
    positions.emplace_back(1,1);
    positions.emplace_back(1,-1);
    m_mesh = new DifferedScreenMesh(positions, positions.size());
    m_material = new DifferedScreenMaterial();

    //ADD COMPONENTS
    auto * renderer = new MeshedRendererComponent();
    this->AddComponent(renderer);
}

void DifferedScreen::Render(RenderingEngine *engine) const
{
    glDisable(GL_DEPTH_TEST);

        MeshedEntity::Render(engine);

    glEnable(GL_DEPTH_TEST);

}

DifferedScreen::~DifferedScreen() {

}

void DifferedScreen::SetTextures(std::vector<Texture*> texs) {
    m_material->setTextures(std::move(texs));
}

void DifferedScreen::AddTexture(Texture *texture) {
    m_material->addTexture(texture);
}
