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

class assModel :public EmptyObject
{
public:
    assModel(World *parent = nullptr);
    ~assModel();

    void loadModel(std::string path);

    virtual void Render(const Shader &shader) override;    


    virtual void SetColor(const glm::vec4 &color) override;
    virtual void Update() override {};

    ObjectType GetObjectType() override
    {
        return m_objType;
    }

protected:
    std::vector<assMesh> m_meshes;
    std::string m_directory;

    void processNode(aiNode *node, const aiScene *scene);
    assMesh processMesh(aiMesh *mesh, const aiScene *scene);

    ObjectType m_objType;    


};