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
#include "Rendering/DirectionalLight.h"
#include "Rendering/PointLight.h"
#include "Rendering/SpotLight.h"
#include "Rendering/Model.h"

const float toRadians = 3.14139265f / 180.0f;
std::vector<Model> modelList;
std::vector<Shader> shaderList;
int CurrentShader = 0;

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

void CreateObjects(){
    //Nanosuit
	modelList.emplace_back("./res/models/Race track/10605_Slot_Car_Race_Track_v1_L3.obj");
}

void CreateShaders(){
	std::map<int, std::string> shaderFiles1;
	
	//Main shader
	shaderFiles1[GL_VERTEX_SHADER] = "./res/shaders/BasicShader.vert";
	shaderFiles1[GL_FRAGMENT_SHADER] = "./res/shaders/Lighting.frag";
    shaderList.emplace_back(shaderFiles1);
	
	std::map<int, std::string> shaderFiles2;
	shaderFiles2[GL_VERTEX_SHADER] = "./res/shaders/DirectionalLightShadowMapShader.vert";
	shaderList.emplace_back(shaderFiles2);
}

void SetupLighting(){
    DirectionalLight::SetupUniforms(shaderList[CurrentShader].getDirectionalLightUniforms(),shaderList[CurrentShader].getShaderProgram());
    SpotLight::SetupUniforms(shaderList[CurrentShader].getSpotLightUniformsArray(),shaderList[CurrentShader].getShaderProgram());
    PointLight::SetupUniforms(shaderList[CurrentShader].getPointLightUniformsArray(),shaderList[CurrentShader].getShaderProgram());

    Material::SetupUniforms(shaderList[CurrentShader].getMaterialUniforms(),shaderList[CurrentShader].getShaderProgram());

    directionalLight = DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-7.0f,-1.0f),
            1.0f, 0.7f,
			1024, 1024);

   // pointLights[pointLightCount] = PointLight(
   //         pointLightCount,glm::vec3(1.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,2.0f),
   //         0.0f, 0.1f,
   //         1.0f,0.4f,0.3f,
			//1024,1024);
   // pointLightCount++;

   // spotLights[spotLightCount] = SpotLight(spotLightCount,
   //         glm::vec3(1.0f,1.0f,1.0f),/*Color*/
   //         glm::vec3(0.0f,0.0f,2.0f),/*position*/
   //         glm::vec3(0.0f,0.0f,1.0f),/*direction*/
   //         0.1f, 0.3f,/*Ambient/diffuse intensity*/
   //         1.0f,0.4f,0.3f, /*attenuation*/
   //         10.0f, /*angle*/
			//1024, 1024);
   // spotLightCount++;
}

void InjectLighting() {
	shaderList[CurrentShader].SetDirectionalLight(&directionalLight);

	//spotLights[CurrentShader].SetAsFlashLight(camera.getPosition(),camera.getDirection());

	shaderList[CurrentShader].SetPointLights(pointLights, pointLightCount);

	shaderList[CurrentShader].SetSpotLights(spotLights, spotLightCount);
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
            15.0f,
            0.5f
    );
}

void ManagementTime() {
	auto now = static_cast<GLfloat>(glfwGetTime());
	deltaTime = now - lastTime;
	lastTime = now;
}

void DrawSceneObjects(bool shadowPass) {
	for (Model model : modelList) {
		model.Draw(&shaderList[CurrentShader],shadowPass);
	}
}

void RenderDirectionalLightShadowMap(DirectionalLight* dlight) {
	CurrentShader = 1; //Use DirectionalLightShadowMapShader

	shaderList[CurrentShader].Bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		//Set view port same size as our shadow-map framebuffer
		glViewport(0, 0, dlight->GetShadowMap()->GetShadowWidth(), dlight->GetShadowMap()->GetShadowHeight());

		dlight->GetShadowMap()->BindFrameBuffer(); //Begin writing

			dlight->SetupLightSpace(shaderList[CurrentShader].getDirectionalLightUniforms(), shaderList[CurrentShader].getShaderProgram());

			DrawSceneObjects(true);

		dlight->GetShadowMap()->UnBindFrameBuffer(); //stop writing

	shaderList[CurrentShader].UnBind();
}

void RenderShadows() {
	RenderDirectionalLightShadowMap(&directionalLight);
}

void RenderScene() {
	CurrentShader = 0; //Use Basic Shader

	window.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	window.ResetViewPort();

		shaderList[CurrentShader].Bind();

			shaderList[CurrentShader].UpdateProjection(projection);

			shaderList[CurrentShader].UpdateView(camera);

			InjectLighting();

			DrawSceneObjects(false);

		shaderList[CurrentShader].UnBind();

	window.Update();
}

void HandleInput() {
	glfwPollEvents();
	camera.handleKeys(window.getKeys(), deltaTime);
	camera.handleMouse(window.getXChange(), window.getYChange());
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

    //Do time management
		ManagementTime();

    //Get * Handle user input events
		HandleInput();

	//Render Shadows
		RenderShadows();

    //Render
		RenderScene();
    }

    return 0;
}