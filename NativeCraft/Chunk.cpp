#include "Chunk.h"


Chunk::Chunk(ivec2 _pos)
{
	GridPosition = _pos;

	vector<Block>* _visibilityData = new vector<Block>();

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				_data[i][j][k] = 1;

				for (int z = 0; z < 6; z++)
				{
					_visibilityData->push_back(Block(vec3(i, j, k), z));
				}
			}
		}
	}

	_vBuffer = new VertexBuffer(_visibilityData);

}

void Chunk::Render(FrameTime* _frTime)
{
	_vBuffer->Render();
}