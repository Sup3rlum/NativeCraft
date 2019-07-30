#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{

	float vertices[] =
	{
		// Z
		0.0f,	0.0f,	0.0f,  // bottom right
		1.0f,	0.0f,	0.0f,  // bottom right
		1.0f,	1.0f,	0.0f,  // bottom left
		0.0f,	1.0f,	0.0f,  // top 


		// Z'     
		0.0f,	0.0f,	1.0f,  // bottom right
		1.0f,	0.0f,	1.0f,  // bottom right
		1.0f,	1.0f,	1.0f,  // bottom left
		0.0f,	1.0f,	1.0f,  // top 


		// X'
		1.0f,	0.0f,	0.0f,  // bottom right
		1.0f,	1.0f,	0.0f,  // bottom right
		1.0f,	1.0f,	1.0f,  // bottom left
		1.0f,	0.0f,	1.0f,  // top 


		// X   
		0.0f,	0.0f,	0.0f,  // bottom right
		0.0f,	1.0f,	0.0f,  // bottom right
		0.0f,	1.0f,	1.0f,  // bottom left
		0.0f,	0.0f,	1.0f,  // top 



		// Y'        
		0.0f,	1.0f,	0.0f,  // bottom right
		1.0f,	1.0f,	0.0f,  // bottom right
		1.0f,	1.0f,	1.0f,  // bottom left
		0.0f,	1.0f,	1.0f,  // top 


		// Y        
		0.0f,	0.0f,	0.0f,  // bottom right
		1.0f,	0.0f,	0.0f,  // bottom right
		1.0f,	0.0f,	1.0f,  // bottom left
		0.0f,	0.0f,	1.0f,  // top 
	};
	float uvs[] =
	{
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	GLuint indices[] =
	{
		// Z

		0,
		1,
		2,

		0,
		2,
		3,


		// Z'
		4,
		5,
		6,

		4,
		6,
		7,

		// X

		8,
		9,
		10,

		8,
		10,
		11,

		// X'

		12,
		13,
		14,

		12,
		14,
		15,

		16,
		17,
		18,

		16,
		18,
		19,

		20,
		21,
		22,

		20,
		22,
		23
	};




	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);



	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	GLuint textureVBO;
	glGenBuffers(1, &textureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);


	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void VertexBuffer::Render()
{
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}