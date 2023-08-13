#version 330 core


in vec4 colorOut;
out vec4 fragColor;

uniform sampler2D textureImage;

void main()
{
	fragColor = colorOut;
}