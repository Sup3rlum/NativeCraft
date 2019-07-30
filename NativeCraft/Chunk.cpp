#include "Chunk.h"


Chunk::Chunk(ivec2 _pos)
{
	GridPosition = _pos;


	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				_data[i][j][k] = 1;
			}
		}
	}

	_vBuffer = new VertexBuffer();

}

void Chunk::Render(FrameTime* _frTime)
{
	_vBuffer->Render();
}