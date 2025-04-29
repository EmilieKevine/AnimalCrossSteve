#include "viewer.h"
#include "textured_sphere.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "node.h"
#include "shader.h"
#include <string>
#include "skybox.h"
#include "textured_cube.h"

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

// Preprocessor check for required definition of TEXTURE_DIR
#ifndef TEXTURE_DIR
#error "TEXTURE_DIR_DIR not defined"
#endif


/**
 * @brief Main application entry point
 *
 * Creates a 3D scene containing:
 * - A textured cube with skybox environment mapping (space mapping)
 * - A textured sphere with simple rotation (Earth in the center of the skybox)
 * - A Phong-lit sphere with orbital animation (A "moon" turning around Earth)
 *
 * @return int Application exit status
 */
int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    // get texture directory
    std::string texture_dir = TEXTURE_DIR;
    
    /****************************
     * Skybox Setup
     ****************************/

    // Load skybox shader
    Shader *skybox_shader = new Shader(shader_dir + "skybox.vert", shader_dir + "skybox.frag");

    // Define paths to skybox textures (6 faces)
    std::vector<std::string> faces = {
            texture_dir + "brick2.jpg",
            texture_dir + "brick2.jpg",
            texture_dir + "brick2.jpg",
            texture_dir + "tapis4.jpg",
            texture_dir + "brick2.jpg",
            texture_dir + "brick2.jpg"
    };

    // Create skybox texture
    Skybox* skybox = new Skybox(faces);

    /****************************
     * Textured Cube Setup
     ****************************/

    // Create cube with skybox
    Shape* cube = new TexturedCube(skybox_shader, skybox);
    glm::mat4 cube_mat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    Node* cube_node = new Node(cube_mat);

    cube_node->add(cube);

    viewer.scene_root->add(cube_node);


    /****************************
     * Animation Setup
     ****************************/

    //Animation management function
    auto updateFunc = [&]() {
        float time = static_cast<float>(glfwGetTime());

        //Cube Animation
        /*cube_node->setTransform(
            glm::rotate(glm::mat4(1.0f), time * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(sin(time) * 1.0f, sin(time) * 1.0f, sin(time) * 1.0f))
        );*/

        //Spheres Animation
    };

    viewer.setUpdateCallback(updateFunc);

    viewer.run();
}
