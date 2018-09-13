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

    inline glm::mat4 GetModel() const{
        glm::mat4 posMatrix = glm::translate(m_pos);

        glm::mat4 rotMatrix = glm::mat4_cast(m_rot);

        glm::mat4 scaleMatrix = glm::scale(m_scale);

        if (m_parent != nullptr && m_parent->HasChanged()){
            return m_parent->GetModel() * (posMatrix * rotMatrix * scaleMatrix);
        }else{
            return (posMatrix * rotMatrix * scaleMatrix); //Identity
        }
    }

    inline glm::vec3& GetPos() { return m_pos; }

    inline void SetPos(const glm::vec3 &pos) { m_pos = pos; }

    inline glm::quat& GetRot() { return m_rot; }

    inline glm::vec3 GetForward(){
        glm::vec3 forward;

        forward.x = 2 * (m_rot.x * m_rot.z - m_rot.w * m_rot.y);
        forward.y = 2 * (m_rot.y * m_rot.z + m_rot.w * m_rot.x);
        forward.z = 1 - 2 * (m_rot.x * m_rot.x + m_rot.y * m_rot.y);

        return forward;
    }

    inline glm::vec3 GetUp(){
        glm::vec3 up;

        up.x = 2 * (m_rot.x * m_rot.y + m_rot.w * m_rot.z);
        up.y = 1 - 2 * (m_rot.x * m_rot.x + m_rot.z * m_rot.z);
        up.z = 2 * (m_rot.y * m_rot.z - m_rot.w * m_rot.x);

        return up;
    }

    inline glm::vec3 GetRight(){
        glm::vec3 right;

        right.x = 1 - 2 * (m_rot.y * m_rot.y + m_rot.z * m_rot.z);
        right.y = 2 * (m_rot.x * m_rot.y - m_rot.w * m_rot.z);
        right.z = 2 * (m_rot.x * m_rot.z + m_rot.w * m_rot.y);

        return right;
    }


    //ROTATIONS
    inline void SetRot(const glm::quat &rot) {
        m_rot = rot;
    }

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

    //TODO: Check if its non uniform
    inline glm::vec3& GetScale()  { return m_scale; }

    inline void SetScale(const glm::vec3 &scale) {
		m_nonUniformScaled = true; //TODO: Check if its non uniform
		m_scale = scale; 
	}

	inline bool isNonUnformScaled() const {
        return m_nonUniformScaled;
    }

	inline void SetParent(Transform* parent){
        m_parent = parent;
    }

    bool HasChanged();

    void Update();

    glm::quat GetTransformedRot() const;

    void LookAt(glm::vec3 point);
protected:
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
