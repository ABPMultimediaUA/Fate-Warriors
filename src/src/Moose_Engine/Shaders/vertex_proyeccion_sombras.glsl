#version 450 core
layout (location = 0) in vec4 aPos;
uniform mat4 luz_proyeccion;
uniform mat4 modelView;
uniform mat4 MVP;


void main()
{
    gl_Position = MVP * luz_proyeccion * aPos;
} 