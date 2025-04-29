#ifndef TEXTURED_CUBE_H
#define TEXTURED_CUBE_H

#include "cube.h"
#include "skybox.h"

class TexturedCube : public Cube {
public:
    TexturedCube(Shader* shader_program, Skybox* skybox);

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint loc_diffuse_map;
    Skybox* skybox;
};

#endif // TEXTURED_CUBE_H