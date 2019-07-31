#include "VisibilityMesh.h"

VisibilityMesh::VisibilityMesh()
{
	Compute();

	_vBuffer = new VertexBuffer(&_positions[0], 4);
}

void VisibilityMesh::Compute(/*const int*** _data*/)
{
/*	if (sizeof(_data) != 65536 * sizeof(float))
	{
		return;
	}*/

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				_positions.push_back(vec3(i, j, k));
			}
		}
	}

	meshSize = _positions.size();

	cout << "Number of points: " << meshSize << endl;
}