#include "Chunk.h"


Chunk::Chunk(Texture* _height, vec2 _pos)
{
	GridPosition = _pos;

	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				float b = _height->GetData(i + _pos.x*16, k + _pos.y*16).x / 4 + 20;

				if (j > b)
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
	_mesh->Compute(_data, _pos);

}

void Chunk::Render(FrameTime* _frTime)
{
	_mesh->Render();
}