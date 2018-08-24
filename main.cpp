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

#include "Window.h"
#include "Shader.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Object.h"
#include "Util.h"
#include "DirectionalLight.h"

const float toRadians = 3.14139265f / 180.0f;
std::vector<Object> objectList;
std::vector<Shader> shaderList;

GLfloat deltaTime;
GLfloat lastTime;

glm::mat4 projection;
Window window;
Camera camera;
DirectionalLight directionalLight;

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
    std::vector<Texture*> textures;
    textures.push_back(new Texture("/home/erick/CLionProjects/MorderOpenGLUdemyTutorial/res/textures/bricks.jpeg"));

    //1
    objectList.push_back(
            Object(
                  new Mesh("../res/objects/monkey3.obj"),
                  new Transform(),
                  textures,
                  new Material(1.0f,32.0f)
            )
        );
}

void CreateShaders(){
    shaderList.emplace_back("../shaders/BasicShader");
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

    camera = Camera(
            glm::vec3(0.0f,0.0f,-4.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            -90.0f,
            0.0f,
            5.0f,
            0.5f
        );

    SetupPerspective();

    DirectionalLight::SetupUniforms(shaderList[0].getDirectionalLightUniforms(),shaderList[0].getShaderProgram());

    Material::SetupUniforms(&shaderList[0]);

    directionalLight = DirectionalLight(glm::vec3(1.0f,1.0f,1.0f),glm::vec3(0.0f,0.0f,-1.0f), 0.2f, 0.3f);

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

                shaderList[0].SetDirectionalLight(&directionalLight);

                for(int i = 0; i < objectList.size(); i++){
                    objectList[i].getTransform()->GetPos() = glm::vec3(0.0,0.0f,-2.5f);
                    objectList[i].getTransform()->GetRot().y = curAngle * toRadians;
                    objectList[i].getTransform()->GetScale() = glm::vec3(0.6,0.6,0.6f);
                    shaderList[0].UpdateModel(*objectList[i].getTransform());

                    objectList[i].getTexture()[0]->Bind(0);

                    objectList[i].getMaterial()->UseMaterial(&shaderList[0]);

                    objectList[i].getMesh()->Draw();
                }

            shaderList[0].UnBind();

        window.Update();

        UpdateTransformations();
    }

    return 0;
}