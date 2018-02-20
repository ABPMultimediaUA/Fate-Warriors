#version 450 core
out vec4 FragColor;
//uniform vec4 vertex_Color;
in vec3 Color;

void main()
{
    FragColor = vec4(Color, 1.0f);
    //FragColor   = vertex_Color;
} 