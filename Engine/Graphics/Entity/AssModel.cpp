#include "AssModel.h"



assModel::assModel(std::string path)
{
    loadModel(path);
}

void assModel::Render(Shader &shader)
{
    for(GLuint i = 0; i < m_meshes.size(); i++)
    {
        m_meshes[i].Render(shader);
    }
}

void assModel::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Error::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);

}

void assModel::processNode(aiNode *node, const aiScene *scene)
{
    // // Process all the node's meshes (if any)
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh,scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

assMesh assModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<assVertex> vertices;
    std::vector<GLuint>indices;
    
    // Process vertex 
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        assVertex vertex;

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;

        vertex.Normal = vector;

        ///////////////
        vertices.push_back(vertex);
    }
    // Process indices
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material

    return assMesh(vertices, indices);
}

