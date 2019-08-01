#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4x4 View;
uniform mat4x4 Projection;

out vec2 fTexCoord;

void main() 
{
    gl_Position = Projection * View * vec4(position + normal, 1.0f);
	fTexCoord = texCoord;
} 