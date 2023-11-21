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

struct assFace
{
    std::vector<glm::vec3> vertices;
};

class assModel :public EmptyObject
{
public:
    assModel(World *parent = nullptr, ObjectType objType = ObjectType::Geometry);
    ~assModel();

    void loadModel(std::string path);

    virtual void Render(const Shader &shader) override;    

    virtual void SetColor(const glm::vec4 &color) override;

    virtual void Update() override {};

    ObjectType GetObjectType() override
    {
        return m_objType;
    }

    std::vector<glm::vec3> GetVertices() const;
    std::vector<assFace> GetFaces() const;

    void SetObjectType(ObjectType objType);

protected:

    std::vector<assMesh> m_meshes;
    std::vector<Buffer> m_buffers;

    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_vertices;

    std::vector<assFace> m_faces;

    Material m_material; 
    ObjectType m_objType;    


    void FillBuffers();   

    void processNode(aiNode *node, const aiScene *scene);

    assMesh processMesh(aiMesh *mesh, const aiScene *scene);    

};