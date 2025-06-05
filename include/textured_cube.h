#ifndef TEXTURED_CUBE_H
#define TEXTURED_CUBE_H

#include "cube.h"
#include "skybox.h"

class TexturedCube : public Cube {
public:
    TexturedCube(Shader* shader_program, Skybox* skybox, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color);

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    glm::vec3 light_position;
    glm::vec3 light_color;
    glm::vec3 object_color;

    GLuint loc_diffuse_map;
    Skybox* skybox;

    // uniform locations
    GLint light_pos_loc;
    GLint light_color_loc;
    GLint object_color_loc;
};

#endif // TEXTURED_CUBE_H