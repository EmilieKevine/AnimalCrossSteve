#include "skybox.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


/**
 * @brief Constructs a Skybox object with cube map textures. Inspired by : https://learnopengl.com/Advanced-OpenGL/Cubemaps
 *
 * @param tex_file Vector of 6 texture file paths for the cube faces in the order:
 *                 right, left, top, bottom, front, back

 */
Skybox::Skybox(const std::vector<std::string>& tex_file, GLenum wrap_mode, GLenum min_filter, GLenum mag_filter)
    : glid_(0)
{
    // Generate OpenGL texture object
    glGenTextures(1, &glid_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, glid_);

    int width, height, nrChannels;

    // Load each of the 6 faces of the cube map
    for (GLuint i = 0; i < tex_file.size(); i++)
    {
        unsigned char* data = stbi_load(tex_file[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << tex_file[i] << std::endl;
            stbi_image_free(data);
        }
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Use clamp to edge to prevent visible seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Skybox::~Skybox() {
    glDeleteTextures(1, &glid_);
}