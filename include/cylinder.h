#pragma once

#include "shape.h"
#include <vector>

class Cylinder : public Shape {
public:
    Cylinder(Shader* shader_program, float height, float radius, int slices, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color);
    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    unsigned int num_indices;
    GLuint VAO;
    GLuint buffers[2];

    glm::vec3 light_position;
    glm::vec3 light_color;
    glm::vec3 object_color;

    // uniform locations
    GLint light_pos_loc;
    GLint light_color_loc;
    GLint object_color_loc;
};
