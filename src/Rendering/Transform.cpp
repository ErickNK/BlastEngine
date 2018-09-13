
#include "Transform.h"

bool Transform::HasChanged()
{
    if(m_parent != nullptr && m_parent->HasChanged())
    {
        return true;
    }

    if(m_pos != m_oldPos)
    {
        return true;
    }

    if(m_rot != m_oldRot)
    {
        return true;
    }

    if(m_scale != m_oldScale)
    {
        return true;
    }

    return false;
}

void Transform::Update()
{
    if(m_initializedOldStuff)
    {
        m_oldPos = m_pos;
        m_oldRot = m_rot;
        m_oldScale = m_scale;
    }
    else
    {
        m_oldPos = m_pos + glm::vec3(1,1,1);
        m_oldRot = m_rot * 0.5f;
        m_oldScale = m_scale + glm::vec3(1,1,1);
        m_initializedOldStuff = true;
    }
}

glm::quat Transform::GetTransformedRot() const
{
    glm::quat parentRot = glm::quat(0,0,0,1);

    if(m_parent)
    {
        parentRot = m_parent->GetTransformedRot();
    }

    return parentRot * m_rot;
}

void Transform::LookAt(glm::vec3 point) {

    assert(point != GetPos()); //Not looking at self.

    glm::vec3 direction = glm::normalize(point - GetPos());

    float dot = glm::dot(glm::vec3(0, 0, 1), direction);
    if (fabs(dot - (-1.0f)) < 0.000001f) {
        SetRot(glm::angleAxis((float)glm::degrees(glm::radians(M_PI)), glm::vec3(0, 1, 0)));
        return;
    }
    else if (fabs(dot - (1.0f)) < 0.000001f) {
        SetRot(glm::quat());
        return;
    }

    float angle = - glm::degrees(glm::radians(acosf(dot)));

    glm::vec3 cross = glm::normalize(glm::cross(glm::vec3(0, 0, 1), direction));
    SetRot(glm::normalize(glm::angleAxis(angle, cross)));
}
