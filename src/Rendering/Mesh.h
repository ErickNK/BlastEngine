//
// Created by erick on 8/12/18.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "../Common/CommonValues.h"

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> color;
    std::vector<unsigned int> indices;
};


class Vertex{
public:
    Vertex() = default;;
    /**
     * Constructor
     * */
    Vertex(
            const glm::vec3& pos,
            const glm::vec2& texCoord = glm::vec2(0, 0),
            const glm::vec3& normal = glm::vec3(0,0,0),
            const glm::vec3& tangent = glm::vec3(0,0,0),
            const glm::vec4& color = glm::vec4(1,1,1,1)
                    ){
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
        this->tangent = tangent;
        this->color = color;
    }

    inline glm::vec3* GetPos() { return &pos;}
    inline glm::vec2* GetTexCoord() { return &texCoord;}
    inline glm::vec3* GetNormal() { return &normal; }
    inline glm::vec3* GetTangent() { return &normal; }
    inline glm::vec4* GetColor() { return &color; }

    inline void SetPos(const glm::vec3 &pos) { Vertex::pos = pos; }
    inline void SetTexCoord(const glm::vec2 &texCoord) { Vertex::texCoord = texCoord; }
    inline void SetNormal(const glm::vec3 &normal) { Vertex::normal = normal; }
    inline void SetTangent(const glm::vec3 &tangent) { Vertex::tangent = tangent; }
    inline void SetColor(const glm::vec4 &color) { Vertex::color = color; }

protected:
    glm::vec3 pos; //For positioning
    glm::vec2 texCoord; //For texturing
    glm::vec3 normal; //For lighting
    glm::vec3 tangent; //For lighting
    glm::vec4 color; //For lighting
};

class Mesh {
public:
    /**
     * Constructor
     * */

    Mesh();
//    explicit Mesh(const std::string& filename);
	Mesh(Vertex* vertices, unsigned int numVertices,unsigned int* indices, unsigned int numIndices);
	Mesh(std::vector<Vertex>& vertices, unsigned int numVertices, std::vector<GLuint>& indices, unsigned int numIndices);

    /**
     * Destructor
     * */
    virtual ~Mesh();

    /**
     * Send the data to be drawn through the pipelines in
     * the gpu.
     * */
    virtual void Draw();
protected:
    virtual void InitMesh(const IndexedModel& model);

    /**
     * The mesh data.
     * */
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    /**
     * Tells OpenGL how much of the vertexArrayObject we want
     * to draw.
     * */
    unsigned int m_drawCount = 0;
};


#endif //OPENGL_MESH_H
