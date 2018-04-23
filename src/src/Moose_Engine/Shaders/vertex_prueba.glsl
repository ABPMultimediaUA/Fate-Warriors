#version 450 core
layout (location = 0) in vec4 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Position;    //VERTICES EN COORDENADAS DE VISTA

uniform mat4 modelView;
uniform mat4 MVP;

void main()
{
    	//TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (modelView * aPos);
    TexCoords = aTexCoords;    
    gl_Position = MVP * aPos;
}