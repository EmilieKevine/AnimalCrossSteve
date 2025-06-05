#pragma once

#include <vector>
#include <glm/glm.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shape.h"

class Shape;

class Node {
public:
    Node(const glm::mat4& transform = glm::mat4(1.0f));
    void add(Node* node);
    void add(Shape* shape);

    glm::vec3 static getPositionFromModelMatrix(const glm::mat4& modelMatrix) {
        return glm::vec3(modelMatrix[3]);
    }

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
    void key_handler(int key) const;
    int id_ = NULL;

    void setTransform(const glm::mat4& transform);
    void resetTransform();
    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);

    const glm::mat4& Node::getTransform() const;
   

    std::vector<Node *> getChildren() {
        return children_;
    }

    std::string getName() {
        return name_;
    }

    void setName(std::string name) {
        name_ = name;
    }

    Node* findNodeByName(const std::string& name);
    void setSteve(GLFWwindow* window); 

    static bool getPiece() {
        return piece;
    }
    
private:
    glm::mat4 transform_;
    std::vector<Node *> children_;
    std::vector<Shape *> children_shape_;
    std::string name_ = "";
    float totalAngle_ = 0;
    float way_ = 1.0f;
    bool direction = true;
    static bool piece;


};
