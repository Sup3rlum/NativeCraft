#include "Chunk.h"

GLuint _indices[6] =
{
	0,1,2,	0,2,3
};


vec3 _vertices[24] =
{
	vec3(0.0f, 1.0f, 0.0f),
	vec3(0.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 1.0f, 0.0f),

	// Z'		1
	vec3(1.0f, 1.0f, 1.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(0.0f, 0.0f, 1.0f),
	vec3(0.0f, 1.0f, 1.0f),

	// Y		2
	vec3(0.0f, 0.0f, 1.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(0.0f, 0.0f, 0.0f),

	// Y'		3
	vec3(0.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 1.0f),
	vec3(0.0f, 1.0f, 1.0f),

	// X		4
	vec3(0.0f, 1.0f, 1.0f),
	vec3(0.0f, 0.0f, 1.0f),
	vec3(0.0f, 0.0f, 0.0f),
	vec3(0.0f, 1.0f, 0.0f),

	// X'		5


	vec3(1.0f, 1.0f, 0.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(1.0f, 1.0f, 1.0f)
};


vec2 uvs[4] =
{
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f),
	vec2(0.0f, 0.0f)

};


vec3 normals[6] =
{
	vec3(0, 0, -1),
	vec3(0, 0, 1),
	vec3(0, -1, 0),
	vec3(0, 1, 0),
	vec3(-1, 0, 0),
	vec3(1, 0, 0)
};



Chunk::Chunk(Texture* _height, ivec2 _pos)
{
	GridPosition = _pos;

	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				int b = _height->GetData(i + _pos.x*16, k + _pos.y*16).x / 2.0f + 20;

				if (j > b)
				{
					_data[i][j][k] = 0;
				}
				else
				{

					if (j < 50)
					{
						_data[i][j][k] = 3;
					}
					else
					{
						if (j == b)
						{
							_data[i][j][k] = 2;
						}
						else
						{
							_data[i][j][k] = 1;
						}
					}
				}


			}
		}
	}

	vec3 _pp = vec3(_pos.x, 0, _pos.y) * 16.0f;

	_box = BoundingBox(_pp, _pp + vec3(16, 256, 16));
	_vBuffer = new VertexBuffer(VertexNormalTexture::Elements);
}
void Chunk::Render(FrameTime* _frTime)
{
	_vBuffer->RenderIndexed(GL_TRIANGLES);
}

#define PAIR_OFFSET(a,b) ncpair(GridPosition.x+a, GridPosition.y+b)
#define CHECK_OFFSET(a,b) check_key(_map, PAIR_OFFSET(a, b)) ? (*_map)[PAIR_OFFSET(a, b)] : NULL

 
bool check_key(level_map* m, uint64_t id)
{
	return (m->find(id) != m->end());
}

void Chunk::ComputeVisibility(level_map* _map)
{
	Chunk* _left, * _right, * _front, * _back;

	_left = CHECK_OFFSET(-1,0);
	_right = CHECK_OFFSET(1, 0);
	_front = CHECK_OFFSET(0, 1);
	_back = CHECK_OFFSET(0, -1);


	int _id = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				_id = _data[i][j][k];

				if (_id != 0)
				{
					if (k > 0 && _data[i][j][k - 1] == 0)
					{
						AddSide(0, vec3(i, j, k), _id);
					}
					if (k < 15 && _data[i][j][k + 1] == 0)
					{
						AddSide(1, vec3(i, j, k), _id);
					}
					if (j > 0 && _data[i][j - 1][k] == 0 || j == 0)
					{
						AddSide(2, vec3(i, j, k), _id);
					}
					if (j < 255 && _data[i][j + 1][k] == 0 || j == 255)
					{

						AddSide(3, vec3(i, j, k), _id);
					}
					if (i > 0 && _data[i - 1][j][k] == 0)
					{
						AddSide(4, vec3(i, j, k), _id);
					}
					if (i < 15 && _data[i + 1][j][k] == 0)
					{
						AddSide(5, vec3(i, j, k), _id);
					}


					if (k == 0)
					{
						if (_back == NULL)
						{
							AddSide(0, vec3(i, j, k), _id);
						}
						else
						{
							if (_back->_data[i][j][15] == 0)
							{
								AddSide(0, vec3(i, j, k), _id);
							}
						}
					}
					if (k == 15)
					{
						if (_front == NULL)
						{
							AddSide(1, vec3(i, j, k), _id);
						}
						else
						{
							if (_front->_data[i][j][0] == 0)
							{
								AddSide(1, vec3(i, j, k), _id);
							}
						}
					}

					if (i == 0)
					{
						if (_left == NULL)
						{
							AddSide(4, vec3(i, j, k), _id);
						}
						else
						{
							if (_left->_data[15][j][k] == 0)
							{
								AddSide(4, vec3(i, j, k), _id);
							}
						}
					}
					if (i == 15)
					{
						if (_right == NULL)
						{
							AddSide(5, vec3(i, j, k), _id);
						}
						else
						{
							if (_right->_data[0][j][k] == 0)
							{
								AddSide(5, vec3(i, j, k), _id);
							}
						}
					}
				}
			}
		}
	}

	_vBuffer->SetIndexedData<VertexNormalTexture>(_vData.data(), _iData.data(), _vData.size(), _iData.size());

}
void Chunk::AddSide(int sideIndex, vec3 offset, int textureIndex)
{
	for (int y = 0; y < 6; y++)
	{
		_iData.push_back(_indices[y] + _vData.size());
	}

	for (int z = sideIndex * 4; z < (sideIndex + 1) * 4; z++)
	{
		_vData.push_back(VertexNormalTexture(offset + _vertices[z], normals[sideIndex], (uvs[z % 4] + BlockIDTextureManager::Get(textureIndex - 1, sideIndex)) / 16.0f));
	}

}