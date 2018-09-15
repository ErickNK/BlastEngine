//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MOUSEPICKER_H
#define MORDEROPENGLUDEMYTUTORIAL_MOUSEPICKER_H


#include <glm/glm.hpp>
#include "../Rendering/Camera/Camera.h"
#include "Window.h"

class MousePicker {

public:
    MousePicker(Camera* m_camera, Window* window);

    void ProcessInput(Input* input, float delta);

    glm::vec2 getNormalizedDeviceCoords(double mouseX, double mouseY);

    glm::vec4 getEyeSpaceCoords(glm::vec4 clipSpaceCoords);

    glm::vec3 getWorldSpaceCoords(glm::vec4 eyeSpaceCoords);

    const glm::vec3 &getCurrentRay() const;

    void setCurrentRay(const glm::vec3 &currentRay);

private:
    glm::vec3 currentRay;

    Window* m_window;
    Camera* m_camera;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MOUSEPICKER_H
