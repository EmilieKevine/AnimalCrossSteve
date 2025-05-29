#include "viewer.h"
#include "textured_sphere.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "node.h"
#include "shader.h"
#include <string>
#include "skybox.h"
#include "textured_cube.h"
#include "model_loader.h"

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

// Preprocessor check for required definition of TEXTURE_DIR
#ifndef TEXTURE_DIR
#error "TEXTURE_DIR not defined"
#endif

#ifndef OBJECT_DIR
#error "OBJECT_DIR not defined"
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

    // get object directory
    std::string object_dir = OBJECT_DIR;
    
    /****************************
     * Skybox Setup
     ****************************/

    // Load skybox shader
    Shader *skybox_shader = new Shader(shader_dir + "skybox.vert", shader_dir + "skybox.frag");

    // Define paths to skybox textures (6 faces)
    std::vector<std::string> faces = {
            texture_dir + "wall.png",
            texture_dir + "wall.png",
            texture_dir + "wall.png",
            texture_dir + "floor.png",
            texture_dir + "wall.png",
            texture_dir + "wall.png"
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


    // Load shader (utilise un shader standard pour MeshShape)
    Shader* model_shader = new Shader(shader_dir + "default.vert", shader_dir + "default.frag");

    // Charge un modèle .obj et le convertit en Node (via MeshShape)
    Node* model_node = ModelLoader::loadModel(object_dir + "Booker\\", "NpcSpDgb.fbx", model_shader);
    if (!model_node) {
        std::cout << "Échec du chargement du modèle" << std::endl;
        return 1;
    }

    if (model_node != nullptr) {
        // Appliquer une transformation initiale (taille et position)
        model_node->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) *
            //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.05f))
        );

        viewer.scene_root->add(model_node); // Ajout à la scène
    }



    Node* model_node2 = ModelLoader::loadModel(object_dir + "objet_lit\\", "Untitled10.fbx", model_shader);
    if (!model_node2) {
        std::cout << "Échec du chargement du modèle" << std::endl;
        return 1;
    }

    if (model_node2 != nullptr) {
        // Appliquer une transformation initiale (taille et position)
        model_node2->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) *
            //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.001f))
        );

        viewer.scene_root->add(model_node2); // Ajout à la scène
    }


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

        glm::vec3 position = glm::vec3(sin(time), 0.0f, cos(time));
        glm::vec3 direction = glm::normalize(glm::vec3(cos(time), 0.0f, -sin(time)));
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        // lookAt(inverse) permet de construire la matrice de rotation
        glm::mat4 rotation = glm::inverse(glm::lookAt(glm::vec3(0.0f), direction, up));

        /*model_node->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), position) *
            rotation *
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.1f))
        );*/

        model_node2->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, -2.0f, 1.75f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))*
            //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.05f))
        );



        //Spheres Animation
    };

    viewer.setUpdateCallback(updateFunc);

    viewer.run();
}
