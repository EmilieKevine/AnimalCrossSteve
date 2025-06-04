#include "cube.h"

#include <iostream>

Cube::Cube(Shader* shader_program) : Shape(shader_program)
{
    // Cube vertex positions
    GLfloat vertex_buffer_data_bis[] = {
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

    for (int i = 0; i < 8; i++) {
        glm::vec3 vertex(vertex_buffer_data_bis[3 * i], vertex_buffer_data_bis[3 * i + 1], vertex_buffer_data_bis[3 * i + 2]);
        glm::vec3 normal = vertex;
        normal = glm::normalize(normal);
        vertex_buffer_data.push_back(vertex);
        normals.push_back(normal);
    }

    // Cube indices
    GLint indices_bis[] = {
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

    for (int i = 0; i < 24; i++) {
        indices.push_back(indices_bis[i]);
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(3, &buffers[0]);

    // Position attribute
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(glm::vec3), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Normal attribute
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    num_indices = static_cast<unsigned int>(indices.size());
}

//Cube drawing
void Cube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffers[0]);
}

void Cube::key_handler(int key) {
    return;
}
