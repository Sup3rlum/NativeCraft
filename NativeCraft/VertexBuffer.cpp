#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(vector<Block>* _data)
{
	primitiveCount = _data->size();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);


	GLuint blockVBO=0;
	glGenBuffers(1, &blockVBO);
	glBindBuffer(GL_ARRAY_BUFFER, blockVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Block) * primitiveCount, _data->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);


	GLint size = 0;

	glBindBuffer(GL_ARRAY_BUFFER, blockVBO);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	cout << size << endl;
	cout << primitiveCount << endl;

}

void VertexBuffer::Render()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_POINTS, 0, primitiveCount);
}