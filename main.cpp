#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonValues.h"
#include "Window.h"
#include "Shader.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Object.h"
#include "Util.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

const float toRadians = 3.14139265f / 180.0f;
std::vector<Object> objectList;
std::vector<Shader> shaderList;

GLfloat deltaTime;
GLfloat lastTime;

glm::mat4 projection;
Window window;
Camera camera;
DirectionalLight directionalLight;
PointLight pointLights[MAX_POINT_LIGHTS];
unsigned int pointLightCount = 0;
SpotLight spotLights[MAX_SPOT_LIGHTS];
unsigned int spotLightCount = 0;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 6.0f;
float triIncrement = 1.0f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float minSize = 0.8f;
float maxSize = 0.1f;

void CreateObjects(){
    //Susanne
    std::vector<Texture*> textures1;
    textures1.push_back(new Texture("/home/erick/CLionProjects/MorderOpenGLUdemyTutorial/res/textures/white-wall.jpg"));

    Transform * transform1 = new Transform();
    transform1->GetPos() = glm::vec3(0.0,0.0f,0.0f);

    objectList.push_back(
            Object(
                  new Mesh("../res/objects/monkey3.obj"),
                  transform1,
                  textures1,
                  new Material(1.0f,32.0f)
            )
        );

    //Floor
    std::vector<Texture*> textures2;
    textures2.push_back(new Texture("/home/erick/CLionProjects/MorderOpenGLUdemyTutorial/res/textures/pine-wood.jpg"));

    Transform * transform2 = new Transform();
    transform2->GetPos() = glm::vec3(0.0,-2.0f,0.0f);

    Vertex vertices[] = {
            Vertex(glm::vec3(-100.0,0.0,-100.0),glm::vec2(0.0,0.0),glm::vec3(0.0,1.0,0.0)),
            Vertex(glm::vec3(100.0,0.0,-100.0),glm::vec2(10.0,0.0),glm::vec3(0.0,1.0,0.0)),
            Vertex(glm::vec3(-100.0,0.0,100.0),glm::vec2(0.0,10.0),glm::vec3(0.0,1.0,0.0)),
            Vertex(glm::vec3(100.0,0.0,100.0),glm::vec2(10.0,10.0),glm::vec3(0.0,1.0,0.0))
    };

    unsigned int indices[] = {
            0,2,1,
            1,2,3
    };

    objectList.push_back(
            Object(
                    new Mesh(
                            vertices,
                            sizeof(vertices)/sizeof(vertices[0]),
                            indices,
                            sizeof(indices)/sizeof(indices[0])
                            ),
                    transform2,
                    textures2,
                    new Material(0.4f,10.0f)
            )
    );
}

void CreateShaders(){
    shaderList.emplace_back("../shaders/BasicShader");
}

void SetupLighting(){
    DirectionalLight::SetupUniforms(shaderList[0].getDirectionalLightUniforms(),shaderList[0].getShaderProgram());

    Material::SetupUniforms(shaderList[0].getMaterialUniforms(),shaderList[0].getShaderProgram());

    directionalLight = DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0f,0.0f),
            0.1f, 0.2f);

    pointLights[pointLightCount] = PointLight(
            pointLightCount,glm::vec3(1.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,2.0f),
            0.0f, 0.1f,
            1.0f,0.4f,0.3f);
    pointLightCount++;

    /* int id, glm::vec3 color, glm::vec3 position, glm::vec3 direction,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat constant, GLfloat linear, GLfloat quadratic,
            GLfloat edge*/
    spotLights[spotLightCount] = SpotLight(spotLightCount,
            glm::vec3(1.0f,1.0f,1.0f),/*Color*/
            glm::vec3(0.0f,0.0f,2.0f),/*position*/
            glm::vec3(0.0f,0.0f,1.0f),/*direction*/
            0.1f, 0.3f,/*Ambient/diffuse intensity*/
            1.0f,0.4f,0.3f, /*attenuation*/
            10.0f);/*angle*/
    spotLightCount++;
}

void SetupPerspective(){
    //Setup projection
    projection = glm::perspective(
            45.0f,
            (GLfloat)window.getBufferWidth()/(GLfloat)window.getBufferHeight(),
            0.1f,
            1000.0f
        );
}

void SetupCamera(){
    camera = Camera(
            glm::vec3(0.0f,0.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            -90.0f,
            0.0f,
            5.0f,
            0.5f
    );
}

void UpdateTransformations(){
    //Translate
    if(direction){
        triOffset += triIncrement;
    }else{
        triOffset -= triIncrement;
    }

    if(abs(triOffset) >= triMaxOffset){
        direction = !direction;
    }

    //Rotate
    curAngle += 1.0f;
    if(curAngle >= 360){
        curAngle -= 360;
    }

    //Scale
    if(sizeDirection){
        curSize += 0.01f;
    }else{
        curSize -= 0.01f;
    }

    if(curSize >= maxSize || curSize <= minSize){
        sizeDirection = !sizeDirection;
    }
}

int main() {
//INIT

    window = Window(1366,768);
    window.Initialize();

    CreateObjects();

    CreateShaders();

    SetupPerspective();

    SetupCamera();

    SetupLighting();

//MAIN LOOP

    while(!window.getShouldClose()){

    //Time Management
        auto now = static_cast<GLfloat>(glfwGetTime());
        deltaTime = now - lastTime;
        lastTime = now;

    //Get * Handle user input events
        glfwPollEvents();
        camera.handleKeys(window.getKeys(), deltaTime);
        camera.handleMouse(window.getXChange(), window.getYChange());

        window.Clear(0.0f,0.0f,0.0f,1.0f);

            shaderList[0].Bind();

                shaderList[0].UpdateProjection(projection);

                shaderList[0].UpdateView(camera);

                spotLights[0].SetFlashLight(camera.getPosition(),camera.getDirection());

                shaderList[0].SetDirectionalLight(&directionalLight);

//                shaderList[0].SetPointLights(pointLights, pointLightCount);

                shaderList[0].SetSpotLights(spotLights, spotLightCount);

                for(int i = 0; i < objectList.size(); i++){
                    shaderList[0].UpdateModel(*objectList[i].getTransform());

                    objectList[i].getTexture()[0]->Bind(0);

                    objectList[i].getMaterial()->UseMaterial(shaderList[0].getMaterialUniforms());

                    objectList[i].getMesh()->Draw();
                }

            shaderList[0].UnBind();

        window.Update();

        UpdateTransformations();
    }

    return 0;
}