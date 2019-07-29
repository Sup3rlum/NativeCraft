#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;


uniform mat4 View;
uniform mat4 Projection;

void main() 
{
    gl_Position = Projection * View * vec4(position, 1.0);
    vertexColor = color;
}