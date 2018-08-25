//
// Created by erick on 8/21/18.
//

#include "Window.h"

Window::Window() {
    width = 800;
    height = 600;
    for(size_t i = 0; i < sizeof(keys); i++){
        keys[i] = false;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight):
    width(windowWidth) ,
    height(windowHeight)
{
    for(size_t i = 0; i < sizeof(keys); i++){
        keys[i] = false;
    }
}

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

//Input Modes
//    glfwSetInputMode(mainWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

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

    //Enable Depth
    glEnable(GL_DEPTH_TEST);

    //Enable Cull face
//    glEnable(GL_CULL_FACE);

//    glCullFace(GL_BACK);

    //Get buffer size information
    glfwGetFramebufferSize(mainWindow,&bufferWidth,&bufferHeight);

    //Set Viewport.
    glViewport(0,0,bufferWidth,bufferHeight);

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
            theWindow->keys[key] = true;
        }else if(action == GLFW_RELEASE){
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouseCallback(GLFWwindow *window, double xPos, double yPos){
    //Get the user pointer of the incoming window
    auto *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(theWindow->mouseFirstMoved){
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    if(theWindow->invertedX) theWindow->XChange = theWindow->lastX - xPos  ;
    else theWindow->XChange = xPos - theWindow->lastX;

    if(theWindow->invertedY) theWindow->YChange = yPos - theWindow->lastY;
    else theWindow->YChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

void Window::createCallbacks() {

    glfwSetKeyCallback(mainWindow, handleKeysCallback);

    glfwSetCursorPosCallback(mainWindow, handleMouseCallback);
}

//GETTERS AND SETTERS

int Window::getBufferWidth() const {
    return bufferWidth;
}

int Window::getBufferHeight() const {
    return bufferHeight;
}

void Window::setInvertedX(bool invertedX) {
    Window::invertedX = invertedX;
}

void Window::setInvertedY(bool invertedY) {
    Window::invertedY = invertedY;
}

const bool *Window::getKeys() const {
    return keys;
}

double Window::getXChange() {
    double lastChange = XChange;
    XChange = 0;
    return lastChange;
}

double Window::getYChange() {
    double lastChange = YChange;
    YChange = 0;
    return lastChange;
}

bool Window::getShouldClose() const {
    return static_cast<bool>(glfwWindowShouldClose(mainWindow));
}

bool Window::isMouseLastMoved() const {
    return mouseLastMoved;
}

bool Window::isMouseFirstMoved() const {
    return mouseFirstMoved;
}

