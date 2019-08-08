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
				float b = _height->GetData(i + _pos.x*16, k + _pos.y*16).x / 3.1 + 20;

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

	vec3 _pp = vec3(_pos.x, 0, _pos.y) * 16.0f;

	_box = BoundingBox(_pp, _pp + vec3(16, 256, 16));
}

void Chunk::Render(FrameTime* _frTime)
{
	_mesh->Render();
}