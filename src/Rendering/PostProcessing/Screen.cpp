//
// Created by erick on 9/21/18.
//

#include "Screen.h"
#include "../Shaders/PostProcessingScreenShader.h"

ScreenMesh::ScreenMesh(std::vector<glm::vec2> pos, unsigned int numVertices) {

    for (unsigned int i = 0; i < numVertices ; i++){
        m_drawCount++;
        positions.push_back(pos[i]);
    }

    InitScreenMesh();
}


void ScreenMesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, m_drawCount); //Draw
    glBindVertexArray(0);

}

void ScreenMesh::InitScreenMesh() {

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

ScreenMaterial::ScreenMaterial(Texture* texture)
        : m_texture(texture){}

void ScreenMaterial::SetTexture(Texture* texture) {
    m_texture = texture;
}

void ScreenMaterial::UseMaterial(Shader * shader) {
    glUniform1i(shader->getUniforms()["texture"], 0);
    if(m_texture != nullptr)m_texture->Bind(0);
}

Screen::Screen() {
    std::vector<glm::vec2> positions;
    positions.emplace_back(-1,1);
    positions.emplace_back(-1,-1);
    positions.emplace_back(1,1);
    positions.emplace_back(1,-1);
    m_screen_mesh = *new ScreenMesh(positions, positions.size());
    m_screen_material = *new ScreenMaterial();
}

void Screen::Render(RenderingEngine *engine)
{
    glDisable(GL_DEPTH_TEST);
    auto * shader = (PostProcessingScreenShader*) engine->BindShader(POST_PROCESSING_SCREEN_SHADER);

        m_screen_material.UseMaterial(shader);

        m_screen_mesh.Draw();

    engine->UnBindShader(TERRAIN_SHADER);
    glEnable(GL_DEPTH_TEST);

}

Screen::~Screen() {

}

void Screen::SetTexture(Texture *texture) {
    m_screen_material.SetTexture(texture);
}
