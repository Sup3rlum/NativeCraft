#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const vec3* _data, int count)
{

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);


	GLuint blockVBO;
	glGenBuffers(1, &blockVBO);
	glBindBuffer(GL_ARRAY_BUFFER, blockVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * count, &_data[0].x, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	GLint size = 0;

	glBindBuffer(GL_ARRAY_BUFFER, blockVBO);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	cout << size << endl;

}

void VertexBuffer::Render()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_POINTS, 0, 5);
}