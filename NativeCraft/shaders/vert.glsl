#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

out vec2 texCoord;

uniform mat4 View;
uniform mat4 Projection;

void main() 
{
    gl_Position = Projection * View * vec4(position, 1.0);
	texCoord = texcoord;
}