#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "shape.h"

class Shape;

class Node {
public:
    Node(const glm::mat4& transform = glm::mat4(1.0f));
    void add(Node* node);
    void add(Shape* shape);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
    void key_handler(int key) const;

    void setTransform(const glm::mat4& transform);
    void resetTransform();
    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);

    const glm::mat4& Node::getTransform() const;
    
private:
    glm::mat4 transform_;
    std::vector<Node *> children_;
    std::vector<Shape *> children_shape_;
};
