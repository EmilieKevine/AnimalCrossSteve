#pragma once
#include "shape.h"  // Inclure shape.h en premier
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class MeshShape : public Shape {
public:
    MeshShape(Shader* shader_program,
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        Texture* texture,
        glm::vec3 material_color = glm::vec3(1.0f));

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;
    ~MeshShape();

private:
    void setupMesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);

    GLuint VAO;
    GLuint VBOs[1];
    GLuint EBO;
    unsigned int num_indices;
    Texture* texture;
    glm::vec3 material_color;
};