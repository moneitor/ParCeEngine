#version 330 core

in vec3 vertexIn;
in vec4 colorIn;
in vec2 textureIn;
in vec3 normalIn;

out vec3 vertexOut;
out vec4 colorOut;
out vec2 textureOut;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normal;

void main()
{
	colorOut = colorIn;
	// colorOut = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	textureOut = textureIn;
	normalOut = normalize(normal * normalIn);

	vertexOut = (model * vec4(vertexIn, 1.0)).xyz;

	gl_Position = proj * view * model * vec4(vertexIn, 1.0);
}