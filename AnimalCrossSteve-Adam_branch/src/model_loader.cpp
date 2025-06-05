#include "model_loader.h"
#include <iostream>
#include <stb_image.h>

Node* ModelLoader::loadModel(const std::string& directory, const std::string& file, Shader* shader) {
    // Read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(directory+file,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace);

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    // Process nodes recursively
    Node* rootNode = new Node();
    processNode(scene->mRootNode, scene, rootNode, shader, directory);

    return rootNode;
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene,
    Node* parent, Shader* shader, const std::string& directory) {

    // Process all meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshShape* shape = processMesh(mesh, scene, shader, directory);
        if (shape) {
            parent->add(shape);
        }
    }


    // Process children recursively
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        Node* childNode = new Node();
        childNode->setName(node->mChildren[i]->mName.C_Str());
        parent->add(childNode);
        processNode(node->mChildren[i], scene, childNode, shader, directory);
    }
}

MeshShape* ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene, Shader* shader, const std::string& directory) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture* texture = nullptr;
    glm::vec3 matColor(1.0f);

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        // Position
        vertex.Position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Normale
        if (mesh->HasNormals()) {
            vertex.Normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }

        // Texture coords
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    // Matériau
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D color(0.f, 0.f, 0.f);
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
            matColor = glm::vec3(color.r, color.g, color.b);
        }
        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString str;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
            std::string texPath = str.C_Str();
            std::string fullPath = texPath; // Ajuste si besoin avec le répertoire
            std::cout << "Je suis dans model_loader, voici le chemin : " << fullPath << std::endl;

            texture = new Texture(directory+fullPath, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        }
    }



    return new MeshShape(shader, vertices, indices, texture, matColor);

}
