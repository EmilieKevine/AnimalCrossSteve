#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "mesh_shape.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class ModelLoader {
public:
    static Node* loadModel(const std::string& directory, const std::string& file, Shader* shader);

private:
    static void processNode(aiNode* node,
        const aiScene* scene,
        Node* parent,
        Shader* shader, const std::string& directory);

    static MeshShape* processMesh(aiMesh* mesh,
        const aiScene* scene,
        Shader* shader, const std::string& directory);
};