#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * aPos;
    FragPos = vec3(model * aPos);
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = aTexCoords;
}