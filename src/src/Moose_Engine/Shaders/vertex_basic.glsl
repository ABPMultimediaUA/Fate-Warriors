#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//out vec4 vertex_Color;
out vec3 Color;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //vertex_Color = aColor;
    Color = aColor;
}