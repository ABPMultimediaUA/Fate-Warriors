#version 450 core

out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
in float rotacion;

// texture samplers
uniform sampler2D texture1;

void main()
{
	float sin_factor = sin(rotacion);
    float cos_factor = cos(rotacion);
	vec2 Pos = vec2((TexCoord.x - 0.5) * (1280 / 720), TexCoord.y - 0.5) * mat2(cos_factor, sin_factor, -sin_factor, cos_factor);
	Pos += 0.5;
	FragColor = texture(texture1, Pos);
}

