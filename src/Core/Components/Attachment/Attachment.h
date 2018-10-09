//
// Created by erick on 10/3/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ATTACHMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_ATTACHMENT_H

#include "../../../Common/CommonValues.h"
#include "../../Input.h"
#include "../../../Rendering/RenderingEngine.h"

template <class A,class B>
class Attachment {
public:
    Attachment() = default;
    explicit Attachment(A* firstEntity, B* secondEntity) :
        m_firstEntity(firstEntity),
        m_secondEntity(secondEntity),
        m_type(NONE) {}

    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(double time, float delta) {}
    virtual void Render(RenderingEngine* engine) const {};
    virtual void SetFirstEntity(A* entity) { m_firstEntity = entity; }
    virtual void SetSecondEntity(B* entity) { m_secondEntity = entity; }
    ComponentTypes getType() { return m_type; }

    A *getFirstEntity(){ return m_firstEntity; }
    B *getSecondEntity() const { return m_secondEntity; }

protected:
    A* m_firstEntity{};
    B* m_secondEntity{};
    ComponentTypes m_type = NONE;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ATTACHMENT_H
