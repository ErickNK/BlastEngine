//
// Created by erick on 8/14/18.
//

#ifndef OPENGL_TRANSFORM_H
#define OPENGL_TRANSFORM_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
    Transform(
            const glm::vec3& pos = glm::vec3(),
            const glm::quat& rot  = glm::quat(),
            const glm::vec3& scale  = glm::vec3(1.0f, 1.0f, 1.0f)
    ): m_pos(pos),
    m_rot(rot),
    m_scale(scale) {}

    //POSITION
    inline glm::vec3& GetPos() { return m_pos; }
    void SetPos(const glm::vec3 &pos) {
        m_pos = pos;
    }
    inline void SetXPos(float d) { m_pos.x = d; }
    inline void SetYPos(float d) { m_pos.y = d; }
    inline void SetZPos(float d) { m_pos.z = d; }

    //ROTATION
    inline glm::quat& GetRot() { return m_rot; }
    inline void SetRot(const glm::quat &rot) { m_rot = rot; }
    inline glm::vec3 GetForward(){ return glm::rotate(m_rot,glm::vec3(0,0,1)); }
    inline glm::vec3 GetUp(){ return glm::rotate(m_rot,glm::vec3(0,1,0)); }
    inline glm::vec3 GetRight(){ return glm::rotate(m_rot,glm::vec3(1,0,0)); }

    inline void Rotate(float angle, glm::vec3 axis){
        m_rot = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    }
    inline void Rotate(glm::vec3 rotation){
        glm::quat key_quat = glm::quat(rotation);
        m_rot = key_quat * m_rot;
    }
    inline void Rotate(glm::quat rotation){
        m_rot = glm::normalize(rotation * m_rot);
    }

    //SCALE
    //TODO: Check if its non uniform
    inline glm::vec3& GetScale()  { return m_scale; }
    inline void SetScale(const glm::vec3 &scale) {
		m_nonUniformScaled = true; //TODO: Check if its non uniform
		m_scale = scale; 
	}
	inline bool isNonUnformScaled() const { return m_nonUniformScaled; }

    inline void SetParent(Transform* parent){
        m_parent = parent;
    }

	glm::mat4 GetModel() const;

    bool HasChanged();

    void Update();

    glm::quat GetTransformedRot() const;

    glm::vec3 GetTransformedPos() const;

    void LookAt(glm::vec3 point);

private:
    glm::vec3 m_pos;
    glm::quat m_rot;
    glm::vec3 m_scale;
	bool m_nonUniformScaled = false;

    Transform* m_parent = nullptr;
    mutable glm::vec3 m_oldPos;
    mutable glm::quat m_oldRot;
    mutable glm::vec3 m_oldScale;
    mutable bool m_initializedOldStuff;
};


#endif //OPENGL_TRANSFORM_H
