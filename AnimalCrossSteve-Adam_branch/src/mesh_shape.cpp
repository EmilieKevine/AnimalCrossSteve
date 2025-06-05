#include "mesh_shape.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

MeshShape::MeshShape(Shader* shader_program,
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices,
    Texture* texture,
    glm::vec3 material_color)
    : Shape(shader_program),
    num_indices(static_cast<unsigned int>(indices.size())),
    texture(texture),
    material_color(material_color) {
    setupMesh(vertices, indices);
}


void MeshShape::setupMesh(const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBOs);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}


void MeshShape::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    glUseProgram(shader_program_);

    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    GLint loc = glGetUniformLocation(shader_program_, "materialColor");
    glUniform3fv(loc, 1, glm::value_ptr(material_color));


    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getGLid());
        glUniform1i(glGetUniformLocation(shader_program_, "diffuse_map"), 0);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}


MeshShape::~MeshShape() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(3, VBOs);
    glDeleteBuffers(1, &EBO);
}