#pragma once

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>

class Triangle : public Shape {
public:
    Triangle(Shader* shader_program, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
    void key_handler(int key);
    virtual ~Triangle();

private:
    GLuint VAO;
    GLuint VBO;

    glm::vec3 light_position;
    glm::vec3 light_color;
    glm::vec3 object_color;

    // uniform locations
    GLint light_pos_loc;
    GLint light_color_loc;
    GLint object_color_loc;
};