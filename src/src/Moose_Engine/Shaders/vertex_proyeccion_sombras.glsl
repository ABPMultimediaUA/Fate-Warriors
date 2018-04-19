#version 450 core
layout (location = 0) in vec4 aPos;
uniform vec3 luz_posicion;
uniform mat4 modelView;
uniform mat4 MVP;


void main()
{
    gl_Position = MVP * aPos;
} 