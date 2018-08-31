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

#include "Core/CommonValues.h"
#include "Rendering/Window.h"
#include "Rendering/Shader.h"
#include "Rendering/Transform.h"
#include "Rendering/Mesh.h"
#include "Rendering/Camera.h"
#include "Rendering/Texture.h"
#include "Rendering/Object.h"
#include "Rendering/DirectionalLight.h"
#include "Rendering/PointLight.h"
#include "Rendering/SpotLight.h"
#include "Rendering/Model.h"

const float toRadians = 3.14139265f / 180.0f;
std::vector<Object> objectList;
std::vector<Model> modelList;
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
    //Nanosuit
	modelList.emplace_back("./res/models/nanosuit/nanosuit.obj");

	//Monkey
	//std::vector<Texture> textures;
	/*Texture texture1("./res/textures/white-wall.jpg", DIFFUSE_TEXTURE);
	Texture texture2("./res/textures/white-wall.jpg", SPECULAR_TEXTURE);
	textures.push_back(texture1);
	textures.push_back(texture2);*/

	/*objectList.emplace_back(
		*new Mesh("./res/models/nanosuit/nanosuit.obj"),
		*new Transform(),
		*new Material(0.5f,32.0f,textures)
	);*/
}

void CreateShaders(){
	std::map<int, std::string> shaderFiles;
	
	//Main shader
	shaderFiles[GL_VERTEX_SHADER] = "./res/shaders/BasicShader.vert";
	shaderFiles[GL_FRAGMENT_SHADER] = "./res/shaders/Lighting.frag";
    shaderList.emplace_back(shaderFiles);
}

void SetupLighting(){
    DirectionalLight::SetupUniforms(shaderList[0].getDirectionalLightUniforms(),shaderList[0].getShaderProgram());

    Material::SetupUniforms(shaderList[0].getMaterialUniforms(),shaderList[0].getShaderProgram());

    directionalLight = DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0f,0.0f),
            0.4f, 0.7f);

    pointLights[pointLightCount] = PointLight(
            pointLightCount,glm::vec3(1.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,2.0f),
            0.0f, 0.1f,
            1.0f,0.4f,0.3f);
    pointLightCount++;

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

void TimeManagement() {
	auto now = static_cast<GLfloat>(glfwGetTime());
	deltaTime = now - lastTime;
	lastTime = now;
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
		TimeManagement();

    //Get * Handle user input events
        glfwPollEvents();
        camera.handleKeys(window.getKeys(), deltaTime);
        camera.handleMouse(window.getXChange(), window.getYChange());

        window.Clear(0.0f,0.0f,0.0f,1.0f);

            shaderList[0].Bind();

                shaderList[0].UpdateProjection(projection);

                shaderList[0].UpdateView(camera);
                
				//spotLights[0].SetFlashLight(camera.getPosition(),camera.getDirection());

                shaderList[0].SetDirectionalLight(&directionalLight);

                //shaderList[0].SetPointLights(pointLights, pointLightCount);

                //shaderList[0].SetSpotLights(spotLights, spotLightCount);

				modelList[0].Draw(&shaderList[0]);

     //           for(int i = 0; i < objectList.size(); i++){
					//shaderList[0].UpdateModel(objectList[i].getTransform());

					//shaderList[0].UpdateNormalMatrix(
					//	//glm::mat3(glm::transpose(glm::inverse(objectlist[i].gettransform()->getmodel())))
					//	glm::mat3(objectList[i].getTransform().GetModel())
					//);

					//objectList[i].getMaterial().UseMaterial(shaderList[0].getMaterialUniforms());

     //               objectList[i].getMesh().Draw();
     //           }

            shaderList[0].UnBind();

        window.Update();

        UpdateTransformations();
    }

    return 0;
}