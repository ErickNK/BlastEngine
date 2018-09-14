//
// Created by erick on 8/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_WINDOW_H
#define MORDEROPENGLUDEMYTUTORIAL_WINDOW_H


#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"

class Window {
public:
    Window();

    Window(GLint windowWidth, GLint windowHeight);

    virtual ~Window();

    void Initialize();

    void Update();

    void Clear(float r, float b, float g, float a);

	void ResetViewPort();

//GETTERS AND SETTERS

    bool getShouldClose() const;

    int getBufferWidth() const;

    int getBufferHeight() const;

    glm::vec2 getCenter() const;

    Input* getInput();
protected:
private:
    int bufferWidth, bufferHeight;

    GLint width, height;

    GLFWwindow *mainWindow;

    Input m_input;

    void createCallbacks();

	void setupSettings();

    static void handleKeysCallback(GLFWwindow *window, int key, int code, int action, int mode);

    static void handleMouseCallback(GLFWwindow *window, double xPos, double yPos);

	static void handleScrollCallback(GLFWwindow *window, double dx, double dy);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WINDOW_H
