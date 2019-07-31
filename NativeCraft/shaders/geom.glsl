#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

in float gData[];

out vec2 texCoord;

uniform mat4 View;
uniform mat4 Projection;

vec3 vertices[24] = vec3[]
(

	// Z 
	vec3(0.0f,	0.0f,	0.0f),
	vec3(1.0f,	0.0f,	0.0f),
	vec3(0.0f,	1.0f,	0.0f),
	vec3(1.0f,	1.0f,	0.0f),

	// Z''
	vec3(0.0f,	0.0f,	1.0f),
	vec3(1.0f,	0.0f,	1.0f),
	vec3(0.0f,	1.0f,	1.0f),
	vec3(1.0f,	1.0f,	1.0f),

		// Y 
	vec3(0.0f,	0.0f,	0.0f),
	vec3(1.0f,	0.0f,	0.0f),
	vec3(0.0f,	0.0f,	1.0f),
	vec3(1.0f,	0.0f,	1.0f),

		// Y' 
	vec3(0.0f,	1.0f,	0.0f),
	vec3(1.0f,	1.0f,	0.0f),
	vec3(0.0f,	1.0f,	1.0f),
	vec3(1.0f,	1.0f,	1.0f),

		// Z 
	vec3(0.0f,  0.0f,	0.0f),
	vec3(0.0f,  1.0f,	0.0f),
	vec3(0.0f,  0.0f,	1.0f),
	vec3(0.0f,  1.0f,	1.0f),

		// Z 
	vec3(1.0f,  0.0f,	0.0f),
	vec3(1.0f,  1.0f,	0.0f),
	vec3(1.0f,  0.0f,	1.0f),
	vec3(1.0f,  1.0f,	1.0f)
);

vec2 uvs[4] = vec2[]
(
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 0.0f),
	vec2(0.0f, 1.0f)

);			



void main() 
{
	for (int i = 0; i < 4; i++)
	{
		gl_Position = Projection * View * (gl_in[0].gl_Position + vec4(vertices[i+int(gData[0])*4],0));
		texCoord = uvs[i];
		EmitVertex();
	}

	EndPrimitive();
}