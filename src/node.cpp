#include "node.h"
#include "shape.h"
#include <iostream>

Node::Node(const glm::mat4& transform) :
    transform_(transform){

        children_ = std::vector<Node*>();
}

void Node::add(Node* node) {
    children_.push_back(node);
}

void Node::add(Shape* shape) {
    children_shape_.push_back(shape);
}

void Node::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    glm::mat4 updatedModel = model * transform_;

    for (auto child : children_) {
        child->draw(updatedModel, view, projection);
    }

    for (auto child : children_shape_) {
        child->draw(updatedModel, view, projection);
    }
}

void Node::key_handler(int key) const {
    for (const auto& child : children_) {
            child->key_handler(key);
    }
}

//Set the Node's Transformation Array
void Node::setTransform(const glm::mat4& transform) {
    transform_ = transform;
}

void Node::resetTransform() {
    transform_ = glm::mat4(1.0f);
}

void Node::translate(const glm::vec3& translation) {
    transform_ = glm::translate(transform_, translation);
}

void Node::rotate(float angle, const glm::vec3& axis) {
    transform_ = glm::rotate(transform_, glm::radians(angle), axis);
}

void Node::scale(const glm::vec3& scale) {
    transform_ = glm::scale(transform_, scale);
}

const glm::mat4& Node::getTransform() const {
    return transform_;
}

Node* Node::findNodeByName(const std::string& name) {
    if (name_ == name) {
        return this;
    }

    for (auto* child : children_) {
        Node* result = child->findNodeByName(name);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}

