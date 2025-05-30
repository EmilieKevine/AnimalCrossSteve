#include "triangle.h"

Triangle::Triangle(Shader* shader_program, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color) :
    Shape(shader_program),
    light_position(light_position),
    light_color(light_color),
    object_color(object_color)
{

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // uniform locations
    light_pos_loc = glGetUniformLocation(this->shader_program_, "lightPos");
    light_color_loc = glGetUniformLocation(this->shader_program_, "lightColor");
    object_color_loc = glGetUniformLocation(this->shader_program_, "objectColor");
}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    // set uniform variables for light and color
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));

    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    /* draw points 0-3 from the currently bound VAO with current in-use shader */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // set uniform variables for light and color
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));
}

void Triangle::key_handler(int key) {
    return;
}
