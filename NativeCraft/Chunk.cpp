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

	_vBuffer = new VertexBuffer(new vec3[4] 
		{  
			vec3(-10.0f, -1.0f, -1.0f),
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 1.0f, 0.0f),
			vec3(0.0f, 2.0f, 0.0f)
		},
		4
	);

}

void Chunk::Render(FrameTime* _frTime)
{
	_vBuffer->Render();
}