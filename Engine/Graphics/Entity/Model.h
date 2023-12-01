#pragma once

#include <string>
#include <vector>
#include "../vendors/glad/glad.h"
// #include <glm/glm.hpp>
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



struct Mesh
{
	std::string name;
	std::string materialName;

	std::vector<GLuint> indices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoords;
};

struct VertexGroup
{
	int v = -1;
	int t = -1;
	int n = -1;

	bool operator==(const VertexGroup& other) const
	{
		return (v == other.v && t == other.t && n == other.n);
	}
};

typedef std::vector<VertexGroup> Face;

class HashFunction
{

public:

	size_t operator()(const VertexGroup& v) const
	{
		return v.v + v.t + v.n;
	}
};

class Model : public EmptyObject
{

public:

	Model(World *parent = nullptr);
	~Model() override;

	bool Load(const std::string& filename);

	virtual void SetColor(const glm::vec4 &color) override;

	virtual void Update() override {};
	virtual void Render(const Shader& shader, Buffer::DrawType drawType) override;

	void ClearModel();

	ObjectType GetObjectType() override
	{
		return m_objType;
	}

private:

	void LoadNode();

	void FillBuffers();
	void SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces);

	std::vector<Mesh> m_meshes;
	std::vector<Buffer> m_buffers;
	std::vector<Material> m_materials;

	ObjectType m_objType;
};
