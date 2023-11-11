#include "AssModel.h"




assModel::assModel(World *parent, ObjectType objType) 
    : EmptyObject(parent), // Initializing the parent on the base class
    m_objType{objType}
{
    // m_objType = ObjectType::Geometry;
    m_material.SetShininess(80.0f);
    m_material.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    m_material.SetDiffuse(glm::vec3(0.2f, 0.2f, 0.2f));
    m_material.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
}

assModel::~assModel()
{
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

    processNode(scene->mRootNode, scene);

    SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    FillBuffers();

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
        m_vertices.push_back(vector);

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;

        vertex.Normal = vector;
        m_normals.push_back(vector);

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


void assModel::FillBuffers()
{
    for (auto& mesh : m_meshes)
	{
		Buffer buffer;
        // std::cout << "Total number of initial verts: " << mesh.Get_Indices().size() << std::endl;
		buffer.CreateBuffer(mesh.Get_Indices().size(), true);

		buffer.FillEBO(&mesh.Get_Indices()[0], mesh.Get_Indices().size() * sizeof(GLuint), Buffer::FillType::Once);
		
		buffer.FillVBO(Buffer::VBOType::VertexBuffer,
			&m_vertices[0].x, m_vertices.size() * sizeof(glm::vec3), Buffer::FillType::Once);

		buffer.FillVBO(Buffer::VBOType::NormalBuffer,
			&m_normals[0].x, m_normals.size() * sizeof(glm::vec3), Buffer::FillType::Once);

		buffer.FillVBO(Buffer::VBOType::ColorBuffer,
			&m_colors[0].x, m_colors.size() * sizeof(glm::vec4), Buffer::FillType::Once);

		m_buffers.push_back(buffer);
	}
}

void assModel::SetColor(const glm::vec4 &color)
{
    for (size_t i = 0; i < m_vertices.size(); i++)
    {
        this->m_colors.push_back(color);
    }
}

std::vector<glm::vec3> assModel::GetVertices() const
{
    return this->m_vertices;
}

void assModel::SetObjectType(ObjectType objType)
{
    this->m_objType = objType;
}



void assModel::Render(const Shader &shader)
{
    EmptyObject::Render(shader);

    for (auto &buffer: m_buffers)
    {
        buffer.LinkEBO();

		buffer.LinkVBO(shader,
			"vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
		buffer.LinkVBO(shader,
			"normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
        buffer.LinkVBO(shader,
			"colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);

        m_material.SendToShader(shader);

		buffer.Render(Buffer::DrawType::Triangles);
		// buffer.Render(Buffer::DrawType::Lines);
    }

}