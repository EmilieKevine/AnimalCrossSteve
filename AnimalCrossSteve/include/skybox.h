#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Skybox {
public:
    Skybox(const std::vector<std::string>& tex_file, GLenum wrap_mode = GL_REPEAT,
        GLenum min_filter = GL_LINEAR, GLenum mag_filter = GL_LINEAR_MIPMAP_LINEAR);
    ~Skybox();

    GLuint getGLid() const { return glid_; }

private:
    GLuint glid_;
};