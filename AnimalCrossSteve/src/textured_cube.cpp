#include "textured_cube.h"

TexturedCube::TexturedCube(Shader* shader_program, Skybox* skybox)
    : Cube(shader_program), skybox(skybox)
{
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "skybox");
}

void TexturedCube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    glUseProgram(this->shader_program_);

    // TODO activate, bind the texture

    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE1);

    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getGLid());

    glUniform1i(loc_diffuse_map, 1); // TODO send the correct texture to the shader

    Cube::draw(model, view, projection);

    // TODO Unbind the texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glDepthFunc(GL_LESS);

    glUseProgram(0);
}
