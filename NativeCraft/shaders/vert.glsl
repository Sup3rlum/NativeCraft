#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 World;

out vec2 gTexCoord;
out vec3 gNormal;

void main() 
{
    gl_Position = Projection * View * World	* vec4(position, 1.0f);
	gTexCoord = texCoord;
	gNormal = normal;

} 