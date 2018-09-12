//
// Created by erick on 8/14/18.
//

#ifndef OPENGL_TRANSFORM_H
#define OPENGL_TRANSFORM_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
        glm::mat4 parentModel;

        glm::mat4 posMatrix = glm::translate(m_pos);

        glm::mat4 rotMatrix = glm::mat4_cast(m_rot);

        glm::mat4 scaleMatrix = glm::scale(m_scale);

        if (m_parent != nullptr){
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

    inline glm::vec3 SetDirection(glm::vec3 direction){
        glm::quat key_quat = glm::quat(direction);
        glm::quat new_quat = key_quat * m_rot; //Multiply the new quat by the old one
        m_rot.x = new_quat.x;
        m_rot.y = new_quat.y;
        m_rot.z = new_quat.z;
        m_rot.w = new_quat.w;
    }

    inline void SetRot(const glm::quat &rot) { m_rot = rot; }

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

protected:
private:
    glm::vec3 m_pos;
    glm::quat m_rot;
    glm::vec3 m_scale;
	bool m_nonUniformScaled = false;

    Transform* m_parent = nullptr;
};


#endif //OPENGL_TRANSFORM_H
