//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUICOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_GUICOMPONENT_H

#include "../Entities/GUIEntity.h"

class Shader;
class Input;

class GUIComponent {
public:
    GUIComponent() = default;
    GUIComponent(GUIEntity* GUI_Entity) : m_GUI_Entity(m_GUI_Entity) {}
    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(float delta) {}
    virtual void Render(RenderingEngine* engine) const {};
    virtual void SetParent(GUIEntity* guiEntity) { m_GUI_Entity = guiEntity; }
protected:
    GUIEntity* m_GUI_Entity{};
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUICOMPONENT_H
