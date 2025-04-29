#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "node.h"
#include <functional>

#include "camera.h"

class Viewer {
public:
    Viewer(int width=1920, int height=1080);

    // Appel d'une fonction de callback pour les mises à jour d'animations
    void setUpdateCallback(std::function<void()> callback) {
        updateCallback = callback;
    }

    void run();
    void on_key(int key);

    Node *scene_root;
    //Camera declaration
    Camera *camera;

private:
    GLFWwindow* win;
    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::function<void()> updateCallback;
};

#endif // VIEWER_H
