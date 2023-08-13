#pragma once

#include <string>
#include "Utilities/Utility.h"
#include "../vendors/glad/glad.h"

class Texture
{

public:

	Texture();

	void Bind() const;
	bool Load(const std::string& filename);
	void Unbind();
	void Unload();

private:

	GLuint m_ID;

};