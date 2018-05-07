#version 450 core

out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D sprite;

void main()
{
	FragColor = texture(sprite, TexCoord);
}