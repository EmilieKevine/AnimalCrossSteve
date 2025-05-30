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
#include "cylinder.h"
#include "triangle.h"


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
    
    Shader* phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");
    Shader* phong2_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong2.frag");
    Shader* color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    // Colors vectors
    glm::vec3 orange = glm::vec3(0.99f, 0.55f, 0.23f);
    glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);

    // Eyes
    glm::vec3 eye_size = glm::vec3(0.3f, 0.37f, 0.1f);
    float eyeX = 0.3f;
    float eyeZ = 0.35f;
    float eyeRot = 40.0f;

    // Pupils
    glm::vec3 pupil_size = glm::vec3(0.58f, 0.6f, 0.2f);
    float pupilZ = 0.4f;

    // Articulations
    float height = 0.8f;
    float radius = 0.05f;
    int slices = 20;

    float articulations_f = radius * 2;
    glm::vec3 articulations_size = glm::vec3(articulations_f, articulations_f, articulations_f);
    float shoulderX = 0.5f;
    float pelvisY = -0.45;

    // Limbs
    float arms_f = 1 / articulations_f;
    glm::vec3 arms_size = glm::vec3(arms_f, arms_f, arms_f);
    float lims_translation = height * 5;

    // Legs
    float legX = 0.2f;
    float legY = -0.8f;

    // Hands and foots
    float hand_f = 0.3f;
    glm::vec3 hand_size = glm::vec3(hand_f, hand_f, hand_f);
    glm::vec3 foot_size = glm::vec3(0.2f, 0.4f, 0.2f);

    // Mouth
    float mouth_f = 0.2f;
    glm::vec3 mouth_size = glm::vec3(mouth_f, mouth_f, mouth_f);
    float mouthX = 0.05f;
    float mouthY = -0.1f;
    float mouthZ = 0.48f;
    float mouthRot = 60.0f;
    float mouthRot2 = 15.0f;
    float mouthHeight = 1.1f;

    /*----------------------------------------------------------------------------------------------------------------*/

    // Steve mat
    glm::mat4 steve_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.32f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* Steve = new Node(steve_mat);

    // Body
    Shape* body = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 body_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.2f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* body_node = new Node(body_mat);
    body_node->add(body);

    // Left eye
    Shape* Leye = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), white);
    glm::mat4 Leye_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(eyeX, 0.0f, eyeZ)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(eyeRot), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), eye_size);
    Node* Leye_node = new Node(Leye_mat);
    Leye_node->add(Leye);

    // Right eye
    Shape* Reye = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), white);
    glm::mat4 Reye_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(-eyeX, 0.0f, eyeZ)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(-eyeRot), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), eye_size);
    Node* Reye_node = new Node(Reye_mat);
    Reye_node->add(Reye);

    // Left pupil
    Shape* Lpupil = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), black);
    glm::mat4 Lpupil_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, pupilZ)) *
        glm::scale(glm::mat4(1.0f), pupil_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Lpupil_node = new Node(Lpupil_mat);
    Lpupil_node->add(Lpupil);

    // Right pupil
    Shape* Rpupil = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), black);
    glm::mat4 Rpupil_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, pupilZ)) *
        glm::scale(glm::mat4(1.0f), pupil_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Rpupil_node = new Node(Rpupil_mat);
    Rpupil_node->add(Lpupil);

    // Letf mouth
    Shape* Lmouth = new Cylinder(phong_shader, mouthHeight, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lmouth_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(mouthX, mouthY, mouthZ)) *
        glm::scale(glm::mat4(1.0f), mouth_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(mouthRot), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(mouthRot2), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* Lmouth_node = new Node(Lmouth_mat);
    Lmouth_node->add(Lmouth);

    // Right mouth
    Shape* Rmouth = new Cylinder(phong_shader, mouthHeight, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), black);
    glm::mat4 Rmouth_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(-mouthX, mouthY, mouthZ)) *
        glm::scale(glm::mat4(1.0f), mouth_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(-mouthRot), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(mouthRot2), glm::vec3(0.0f, -1.0f, 0.0f));
    Node* Rmouth_node = new Node(Rmouth_mat);
    Rmouth_node->add(Rmouth);

    // Left shoulder
    Shape* Lshoulder = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lshoulder_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(shoulderX, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), articulations_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    Node* Lshoulder_node = new Node(Lshoulder_mat);
    Lshoulder_node->add(Lshoulder);

    // Right shoulder
    Shape* Rshoulder = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rshoulder_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(-shoulderX, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), articulations_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Node* Rshoulder_node = new Node(Rshoulder_mat);
    Rshoulder_node->add(Rshoulder);

    // Letf arm
    Shape* Larm = new Cylinder(phong2_shader, height, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Larm_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(lims_translation, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), arms_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* Larm_node = new Node(Larm_mat);
    Larm_node->add(Larm);

    // Right arm
    Shape* Rarm = new Cylinder(phong2_shader, height, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rarm_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(-lims_translation, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), arms_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* Rarm_node = new Node(Rarm_mat);
    Rarm_node->add(Rarm);

    // Letf hand
    Shape* Lhand = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lhand_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.5f)) *
        glm::scale(glm::mat4(1.0f), hand_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Lhand_node = new Node(Lhand_mat);
    Lhand_node->add(Lhand);

    // Right hand
    Shape* Rhand = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rhand_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f)) *
        glm::scale(glm::mat4(1.0f), hand_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Rhand_node = new Node(Rhand_mat);
    Rhand_node->add(Rhand);


    // Left pelvis
    Shape* Lpelvis = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lpelvis_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(legX, pelvisY, 0.0f)) *
        glm::scale(glm::mat4(1.0f), articulations_size);
    //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    Node* Lpelvis_node = new Node(Lpelvis_mat);
    Lpelvis_node->add(Lpelvis);

    // Right pelvis
    Shape* Rpelvis = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rpelvis_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(-legX, pelvisY, 0.0f)) *
        glm::scale(glm::mat4(1.0f), articulations_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Rpelvis_node = new Node(Rpelvis_mat);
    Rpelvis_node->add(Rpelvis);

    // Letf leg
    Shape* Lleg = new Cylinder(phong2_shader, height, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lleg_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -lims_translation, 0.0f)) *
        glm::scale(glm::mat4(1.0f), arms_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Lleg_node = new Node(Lleg_mat);
    Lleg_node->add(Lleg);

    // Right leg
    Shape* Rleg = new Cylinder(phong2_shader, height, radius, slices, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rleg_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -lims_translation, 0.0f)) *
        glm::scale(glm::mat4(1.0f), arms_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Rleg_node = new Node(Rleg_mat);
    Rleg_node->add(Rleg);

    // Letf foot
    Shape* Lfoot = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Lfoot_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.4f)) *
        glm::scale(glm::mat4(1.0f), foot_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Lfoot_node = new Node(Lfoot_mat);
    Lfoot_node->add(Lfoot);

    // Right foot
    Shape* Rfoot = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 Rfoot_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.4f)) *
        glm::scale(glm::mat4(1.0f), foot_size) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* Rfoot_node = new Node(Rfoot_mat);
    Rfoot_node->add(Rfoot);

    // Tail
    Shape* tail = new Triangle(phong2_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), orange);
    glm::mat4 tail_mat =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* tail_node = new Node(tail_mat);
    tail_node->add(tail);

    //Eyes
    Leye_node->add(Lpupil_node);
    Reye_node->add(Rpupil_node);
    body_node->add(Leye_node);
    body_node->add(Reye_node);

    // Mouth
    body_node->add(Lmouth_node);
    body_node->add(Rmouth_node);

    // Articulations
    body_node->add(Lshoulder_node);
    body_node->add(Rshoulder_node);
    body_node->add(Lpelvis_node);
    body_node->add(Rpelvis_node);

    // Hands and arms
    Larm_node->add(Lhand_node);
    Rarm_node->add(Rhand_node);
    Lshoulder_node->add(Larm_node);
    Rshoulder_node->add(Rarm_node);

    // Feet and legs
    Lleg_node->add(Lfoot_node);
    Rleg_node->add(Rfoot_node);
    Lpelvis_node->add(Lleg_node);
    Rpelvis_node->add(Rleg_node);

    // The rest
    body_node->add(tail_node);
    Steve->add(body_node);

    Steve->id_ = 1;
    Lpelvis_node->id_ = 2;
    Rpelvis_node->id_ = 3;

    Rshoulder_node->id_ = 4;
    Lshoulder_node->id_ = 5;
    //Steve->setSteve(viewer.getWin()); 

    // 15. Ajoute Steve à la scène
    viewer.scene_root->add(Steve);


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


    Node* model_node3 = ModelLoader::loadModel(object_dir + "Pendulum Clock\\", "FtrClockPendulumWall.dae", model_shader);
    if (!model_node3) {
        std::cout << "Échec du chargement du modèle" << std::endl;
        return 1;
    }

    if (model_node3 != nullptr) {
        // Appliquer une transformation initiale (taille et position)
        model_node3->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) *
            //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.05f))
        );

        viewer.scene_root->add(model_node3); // Ajout à la scène
    }


    /****************************
     * Animation Setup
     ****************************/

    //Animation management function
    auto updateFunc = [&]() {
        float time = static_cast<float>(glfwGetTime());

        Steve->setSteve(viewer.getWin());

        Lpelvis_node->setSteve(viewer.getWin());
        Rpelvis_node->setSteve(viewer.getWin());

        Rshoulder_node->setSteve(viewer.getWin());
        Lshoulder_node->setSteve(viewer.getWin());

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

        model_node3->setTransform(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 2.0f))*
            //glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))*
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))*
            glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))*
            glm::scale(glm::mat4(1.0f), glm::vec3(0.08f))
        );



        //Spheres Animation
    };

    viewer.setUpdateCallback(updateFunc);
    viewer.run();
}
