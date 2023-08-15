#pragma once


#include <string>
#include <vector>
#include "../vendors/glad/glad.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../Material.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "../Utilities/Utility.h"
#include "../Input.h"
#include "EmptyObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Utilities/Utility.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssMesh.h"

class assModel
{
public:
    assModel(std::string path);
    void Render(Shader &shader);

    

private:
    std::vector<assMesh> m_meshes;
    std::string m_directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    assMesh processMesh(aiMesh *mesh, const aiScene *scene);
};