#version 450 core
out vec4 FragColor;
//uniform vec4 vertex_Color;
in vec2 TexCoords;
in vec3 Position;    #VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;

void main()
{
    FragColor = vec4(0,1,0, 1.0f);
    
} 