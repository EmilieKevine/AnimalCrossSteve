#include "node.h"
#include "shape.h"
#include <iostream>

bool Node::piece = true;

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



void Node::setSteve(GLFWwindow* win) {
    
    float move_speed = 0.002f;
    
    if (id_ == 1) {
        /*transform_ =
            transform_ *
            glm::rotate(glm::mat4(1.0f), glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));*/

        glm::vec3 position = getPositionFromModelMatrix(transform_);
        //std::cout << position[0] << "," << position[1] << "," << position[2] << std::endl;
        double delta = (direction ? -1.0f : 1.0f);

        if (piece) {
            if (!(position[2] > -2)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[2] < 2)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[0] > -2)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[0] < 2) && !(position[2] > -1.32f && position[2] < -0.32f)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                //piece = true;
                return;
            }
        }
        else {
            if (!(position[2] > -2)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[2] < 2)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[0] > 2) && !(position[2] > -1.32f && position[2] < -0.32f)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                return;
            }
            if (!(position[0] < 6)) {
                transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, delta));
                //piece = false;
                return;
            }
        }

        if (position[0] > 2) {
            piece = false;
        }
        else {
            piece = true;
        }

        if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
        {
            direction = true;
            transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, move_speed));
        }
        if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            direction = false;
            transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -move_speed));
        }
        if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            //transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0.0f, 0.0f));
            transform_ =
                transform_ *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            //transform_ = transform_ * glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0.0f, 0.0f));
            transform_ =
                transform_ *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.05f), glm::vec3(0.0f, -1.0f, 0.0f));
        }


        if (glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS)
        {
            transform_ =
                transform_ *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.1f), glm::vec3(0.0f, -1.0f, 0.0f));
        }
        if (glfwGetKey(win, GLFW_KEY_J) == GLFW_PRESS)
        {
            transform_ =
                transform_ *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

    }

    else if (id_ > 1) {

        float angle_max = 20.0f;
        float angle = 0.1f;

        if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
        {
            totalAngle_ += angle * way_;
            float side = 1.0f;
            if (totalAngle_ > angle_max) { way_ = -way_; }
            if (totalAngle_ < -angle_max) { way_ = -way_; }

            if (id_ == 3) { side = -side; }
            if (id_ >= 4) {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * -side * way_), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * side * way_), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        else if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            totalAngle_ += angle * way_;
            float side = 1.0f;
            if (totalAngle_ > angle_max) { way_ = -way_; }
            if (totalAngle_ < -angle_max) { way_ = -way_; }

            if (id_ == 3) { side = -side; }
            if (id_ >= 4) {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * -side * way_), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * side * way_), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        else if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            totalAngle_ += angle * way_;
            float side = 1.0f;
            if (totalAngle_ > angle_max) { way_ = -way_; }
            if (totalAngle_ < -angle_max) { way_ = -way_; }

            if (id_ == 3) { side = -side; }
            if (id_ >= 4) {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * -side * way_), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * side * way_), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        else if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            totalAngle_ += angle * way_;
            float side = 1.0f;
            if (totalAngle_ > angle_max) { way_ = -way_; }
            if (totalAngle_ < -angle_max) { way_ = -way_; }

            if (id_ == 3) { side = -side; }
            if (id_ >= 4) {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * -side * way_), glm::vec3(0.0f, 1.0f, 0.0f));
            }
            else {
                transform_ =
                    transform_ *
                    glm::rotate(glm::mat4(1.0f), glm::radians(angle * side * way_), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        else {

            if (totalAngle_ != 0) {

                float angle = 0.1f;
                float side = 1.0f;
                if (totalAngle_ > 0) { side = -side; }
                totalAngle_ += angle * side;

                if (id_ == 3) { side = -side; }
                if (id_ >= 4) {
                    transform_ =
                        transform_ *
                        glm::rotate(glm::mat4(1.0f), glm::radians(angle * -side), glm::vec3(0.0f, 1.0f, 0.0f));
                }
                else {
                    transform_ =
                        transform_ *
                        glm::rotate(glm::mat4(1.0f), glm::radians(angle * side), glm::vec3(1.0f, 0.0f, 0.0f));
                }
            
            }
        
        }


}


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

