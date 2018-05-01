#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 10.0f;
    TexCoords = aTexCoord;
    ParticleColor = color;
    gl_Position = projection* view * vec4((aPos) + offset, 1.0);
}
