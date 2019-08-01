#include "Chunk.h"


Chunk::Chunk(ivec2 _pos)
{
	GridPosition = _pos;

	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				if (i + j + k > 60)
				{
					_data[i][j][k] = 0;
				}
				else
				{
					_data[i][j][k] = 1;
				}
			}
		}
	}

	_mesh = new VisibilityMesh();
	_mesh->Compute(_data);
}

void Chunk::Render(FrameTime* _frTime)
{
	_mesh->Render();
}