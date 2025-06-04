#include "textured_cube.h"

TexturedCube::TexturedCube(Shader* shader_program, Skybox* skybox, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color)
    : Cube(shader_program), skybox(skybox),
    light_position(light_position),
    light_color(light_color),
    object_color(object_color)
{
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "skybox");

    light_pos_loc = glGetUniformLocation(this->shader_program_, "lightPos");
    light_color_loc = glGetUniformLocation(this->shader_program_, "lightColor");
    object_color_loc = glGetUniformLocation(this->shader_program_, "objectColor");
}

void TexturedCube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    glUseProgram(this->shader_program_);

    // TODO activate, bind the texture

    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE1);

    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getGLid());

    glUniform1i(loc_diffuse_map, 1); // TODO send the correct texture to the shader

    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));

    Cube::draw(model, view, projection);

    // TODO Unbind the texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glDepthFunc(GL_LESS);

    glUseProgram(0);
}
