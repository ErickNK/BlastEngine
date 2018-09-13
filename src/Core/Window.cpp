//
// Created by erick on 8/21/18.
//

#include "Window.h"

Window::Window() {
    width = 800;
    height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight):
    width(windowWidth) ,
    height(windowHeight) {}

void Window::Initialize(){
//GLFW

    //Initialize GLFW
    if(!glfwInit()){
        printf("GLFW Initialization Failed");
        glfwTerminate();
    }

    //Setup GLFW window properties
    //OpenGL version : 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    //Profile : No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE); //Allow forwards compatibility

    //Create Window and Context
    mainWindow = glfwCreateWindow(width,height,"Test", nullptr, nullptr);
    if(!mainWindow){
        printf("GLFW Window Creation Failed");
        glfwTerminate();
    }


//GLEW

    //Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow); //Make the mainWindow's context, the current one.

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    //Initialize GLEW
    GLenum status = glewInit();
    if(status != GLEW_OK){
        printf("GLEW Initialization Failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
    }

//VIEWPORT

    //Get buffer size information
    glfwGetFramebufferSize(mainWindow,&bufferWidth,&bufferHeight);

    //Set Viewport.
    glViewport(0,0,bufferWidth,bufferHeight);

//SETTINGS
	
	setupSettings();

//CALLBACKS

    //Set user pointer of a window so that callbacks can return a GLFW window that has a user pointer as "this" class
    glfwSetWindowUserPointer(mainWindow,this);

    //Callbacks
    createCallbacks();
}

Window::~Window() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}


void Window::Update() {
    //Swap buffers : Draw to screen
    glfwSwapBuffers(mainWindow);
}

void Window::Clear(float r, float b, float g, float a) {
    glClearColor(r,b,g,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::handleKeysCallback(GLFWwindow *window, int key, int code, int action, int mode) {
    //Get the user pointer of the incoming window
    auto *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    //Close window on escape
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window,GL_TRUE);
    }

    //Store key state
    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            theWindow->m_input.getKeys()[key] = true;
        }else if(action == GLFW_RELEASE){
            theWindow->m_input.getKeys()[key] = false;
        }
    }
}

void Window::handleMouseCallback(GLFWwindow *window, double xPos, double yPos){
    //Get the user pointer of the incoming window
    auto *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(theWindow->m_input.isMouseFirstMoved()){
        theWindow->m_input.setLastX(xPos);
        theWindow->m_input.setLastY(yPos);
        theWindow->m_input.setMouseFirstMoved(false);
    }

    if(theWindow->m_input.isInvertedX()) theWindow->m_input.setXChange(theWindow->m_input.getLastX() - xPos);
    else theWindow->m_input.setXChange(xPos - theWindow->m_input.getLastX());

    if(theWindow->m_input.isInvertedY()) theWindow->m_input.setYChange(yPos - theWindow->m_input.getLastY());
    else theWindow->m_input.setYChange(theWindow->m_input.getLastY() - yPos);

    theWindow->m_input.setLastX(xPos);
    theWindow->m_input.setLastY(yPos);
}

void Window::createCallbacks() {

    glfwSetKeyCallback(mainWindow, handleKeysCallback);

    glfwSetCursorPosCallback(mainWindow, handleMouseCallback);
}

void Window::setupSettings(){
	//Input Modes
	//    glfwSetInputMode(mainWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	//Enable Gamma Correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	//Enable Depth
	glEnable(GL_DEPTH_TEST);

}

void Window::ResetViewPort() {
	//Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set Viewport.
	glViewport(0, 0, bufferWidth, bufferHeight);
}

//GETTERS AND SETTERS

int Window::getBufferWidth() const {
    return bufferWidth;
}

int Window::getBufferHeight() const {
    return bufferHeight;
}

bool Window::getShouldClose() const {
    return static_cast<bool>(glfwWindowShouldClose(mainWindow));
}

Input* Window::getInput(){
    return &m_input;
}

glm::vec2 Window::getCenter() const {
    return glm::vec2(getBufferWidth()/2, getBufferHeight()/2);
}

