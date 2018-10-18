//
// Created by erick on 10/10/18.
//

#ifndef BLASTENGINE_SCREEN_H
#define BLASTENGINE_SCREEN_H


#include "../../Core/Entities/MeshedEntity.h"
#include <vector>
#include "../Material.h"
#include "../Texture.h"
#include "../Mesh.h"
#include "../RenderingEngine.h"
/*--------------------------------------
 *
 *  DifferedScreenMesh
 *
 *--------------------------------------
 * */
class DifferedScreenMesh : public Mesh{
public:
    DifferedScreenMesh() = default;

    DifferedScreenMesh(std::vector<glm::vec2> positions, unsigned int numVertices);

    void Draw() override;

    void InitDifferedScreenMesh();

private:
    std::vector<glm::vec2> positions;
};

/*--------------------------------------
 *
 *  DifferedScreenMaterial
 *
 *--------------------------------------
 * */
class DifferedScreenMaterial : public Material{
public:
    DifferedScreenMaterial();

    explicit DifferedScreenMaterial(std::vector<Texture*>& textures);

    void UseMaterial(Shader * shader) override;
};

/*--------------------------------------
 *
 *  DifferedScreen
 *
 *--------------------------------------
 * */
class DifferedScreen : public MeshedEntity{
public:
    DifferedScreen();

    ~DifferedScreen() override;

    void SetTextures(std::vector<Texture*> texs);

    void Render(RenderingEngine *engine) const override;

    void AddTexture(Texture *texture);

protected:
    mutable DifferedScreenMesh m_screen_mesh;
    mutable DifferedScreenMaterial m_screen_material;
};


#endif //BLASTENGINE_SCREEN_H
