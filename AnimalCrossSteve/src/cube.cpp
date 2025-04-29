#include "cube.h"

#include <iostream>

Cube::Cube(Shader* shader_program) : Shape(shader_program)
{
    // Cube vertex positions
    GLfloat vertex_buffer_data[] = {
        // positions          
        -2.0f, -2.0f,  2.0f,
         2.0f, -2.0f,  2.0f,
         2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f,
        -2.0f,  2.0f,  2.0f,
         2.0f,  2.0f,  2.0f,
         2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f 
    };

    // Cube indices
    GLint indices[] = {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        /*4, 5, 6,
        6, 7, 4,*/
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0
        // Front
        /*3, 7, 6,
        6, 2, 3*/
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, &buffers[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

//Cube drawing
void Cube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffers[0]);
}

void Cube::key_handler(int key) {
    return;
}
