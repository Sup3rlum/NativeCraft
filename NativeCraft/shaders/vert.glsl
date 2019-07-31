#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in float data;

out float gData;

void main() 
{
    gl_Position = vec4(position, 1.0f);
	gData = data;

} 