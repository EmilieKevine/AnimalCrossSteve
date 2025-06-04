#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include "shader.h"
#include <vector>
#include <GL/glew.h>

class Cube : public Shape {
public:
    Cube(Shader* shader_program);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
    void key_handler(int key);
    virtual ~Cube();

private:

    std::vector<glm::vec3> vertex_buffer_data;
    std::vector<unsigned int> indices;

    unsigned int num_indices;

    GLuint VAO;
    GLuint buffers[2];
};

#endif