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

class Window {
public:
    Window();

    Window(GLint windowWidth, GLint windowHeight);

    virtual ~Window();

    void Initialize();

    void Update();

    void Clear(float r, float b, float g, float a);

//GETTERS AND SETTERS

    bool getShouldClose() const;

    int getBufferWidth() const;

    int getBufferHeight() const;

    const bool *getKeys() const;

    double getXChange();

    double getYChange();

    void setInvertedX(bool invertedX);

    void setInvertedY(bool invertedY);

    bool isMouseLastMoved() const;

    bool isMouseFirstMoved() const;

protected:
private:
    int bufferWidth, bufferHeight;

    GLint width, height;

    GLFWwindow *mainWindow;

    bool keys[1024];

    double lastX;
    double lastY;
    double XChange;
    double YChange;
    bool invertedX = false;
    bool invertedY = false;
    bool mouseFirstMoved = true;
    bool mouseLastMoved = false;

    void createCallbacks();

	void setupSettings();

    static void handleKeysCallback(GLFWwindow *window, int key, int code, int action, int mode);

    static void handleMouseCallback(GLFWwindow *window, double xPos, double yPos);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WINDOW_H
