#include "VisibilityMesh.h"

GLuint _indices[36] =
{
	0,1,2,		0,2,3, 
	4,5,6,		4,6,7,
	8,9,10,		8,10,11,
	12,13,14,	12,14,15,
	16,17,18,	16,18,19,
	20,21,22,	20,22,23
};


vec3 _vertices[24] =
{

	vec3(0.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 1.0f, 0.0f),
	vec3(0.0f, 1.0f, 0.0f),
	
	// Z'		1
	vec3(0.0f, 0.0f, 1.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(1.0f, 1.0f, 1.0f),
	vec3(0.0f, 1.0f, 1.0f),
	
	// Y		2
	vec3(0.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 0.0f, 1.0f),
	vec3(0.0f, 0.0f, 1.0f),
	
	// Y'		3
	vec3(0.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 1.0f),
	vec3(0.0f, 1.0f, 1.0f),
	
	// X		4
	vec3(0.0f, 0.0f, 0.0f),
	vec3(0.0f, 1.0f, 0.0f),
	vec3(0.0f, 1.0f, 1.0f),
	vec3(0.0f, 0.0f, 1.0f),
	
	// X'		5
	vec3(1.0f, 0.0f, 0.0f),
	vec3(1.0f, 1.0f, 0.0f),
	vec3(1.0f, 1.0f, 1.0f),
	vec3(1.0f, 0.0f, 1.0f)
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

VisibilityMesh::VisibilityMesh()
{
	_vBuffer = new VertexBuffer(VertexNormalTexture::Elements);

}

void VisibilityMesh::Compute(unsigned int _data[16][256][16], vec2 _grid)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				if (_data[i][j][k] != 0)
				{
					if (k > 0 && _data[i][j][k - 1] == 0 || k == 0)
					{
						AddSide(0, vec3(i, j, k));
					}
					if (k < 15 && _data[i][j][k + 1] == 0 || k == 15)
					{
						AddSide(1, vec3(i, j, k));
					}
					if (j > 0 && _data[i][j - 1][k] == 0 || j == 0)
					{
						AddSide(2, vec3(i, j, k));
					}
					if (j < 255 && _data[i][j + 1][k] == 0 || j == 255)
					{

						AddSide(3, vec3(i, j, k));
					}
					if (i > 0 && _data[i - 1][j][k] == 0 || i == 0)
					{
						AddSide(4, vec3(i, j, k));
					}
					if (i < 15 && _data[i + 1][j][k] == 0 || i == 15)
					{
						AddSide(5, vec3(i, j, k));
					}
				}
			}
		}
	}

	_vBuffer->SetIndexedData<VertexNormalTexture>(_vData.data(), _iData.data(), _vData.size(), _iData.size());
}
void VisibilityMesh::AddSide(int sideIndex, vec3 offset)
{
	for (int y = 0; y < 6; y++)
	{
		_iData.push_back(_indices[y] + _vData.size());
	}

	for (int z = sideIndex*4; z < (sideIndex+1)*4; z++)
	{
		_vData.push_back(VertexNormalTexture(offset + _vertices[z], normals[sideIndex], uvs[z % 4]));
	}

}
void VisibilityMesh::Render()
{
	_vBuffer->RenderIndexed(GL_TRIANGLES);
}