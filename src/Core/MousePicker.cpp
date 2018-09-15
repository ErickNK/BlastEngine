//
// Created by erick on 9/15/18.
//

#include "MousePicker.h"

MousePicker::MousePicker(Camera* m_camera,Window* window)
:m_camera(m_camera), m_window(window) {}

const glm::vec3 &MousePicker::getCurrentRay() const {
    return currentRay;
}

void MousePicker::setCurrentRay(const glm::vec3 &currentRay) {
    MousePicker::currentRay = currentRay;
}

void MousePicker::ProcessInput(Input *input, float delta) {
    //Convert to normalized device coors
    glm::vec2 normalizedDeviceCoords =
            getNormalizedDeviceCoords(input->getLastX(),input->getLastY());

    //To clipSpace. Set Z to -1.0f so it can point inwards as a direction.
    glm::vec4 clipSpaceCoord = glm::vec4(normalizedDeviceCoords.x,normalizedDeviceCoords.y,-1.0f,1.0f);

    //To EyeSpace
    glm::vec4 eyeSpaceCoord = getEyeSpaceCoords(clipSpaceCoord);

    //To WorldSpace
    currentRay = getWorldSpaceCoords(eyeSpaceCoord);

}

glm::vec2 MousePicker::getNormalizedDeviceCoords(double mouseX, double mouseY){
    auto x = static_cast<float>((2.0f * mouseX) / m_window->getBufferWidth() - 1.0f);
    auto y = static_cast<float>((2.0f * mouseY) / m_window->getBufferHeight() - 1.0f);
    return glm::vec2(x, -y);
}

glm::vec4 MousePicker::getEyeSpaceCoords(glm::vec4 clipSpaceCoords){
    glm::vec4 coords = glm::inverse(m_camera->getProjection()) * clipSpaceCoords;
    return glm::vec4(coords.x,coords.y,-1.0f,0);
}

glm::vec3 MousePicker::getWorldSpaceCoords(glm::vec4 eyeSpaceCoords){
    glm::vec4 coords = glm::inverse(m_camera->getViewMatrix()) * eyeSpaceCoords;
    return glm::normalize(glm::vec3(coords.x,coords.y,coords.z));
}
