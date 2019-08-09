#pragma once

#include "nchfx.h"

template<typename T>
class LinkedGrid2D
{
	struct Node
	{
		T* data, _left, _right, _front, _back;
	};

	Node* _internal;

	T* Get(int x, int y)
	{
		return NULL;
	}

	void Set(T* _t, int x, int y)
	{

	}


};