#pragma once

#include "BoundingBox.h"

class ColumnFrustum
{
public:
	bool Contains(BoundingBox _box);
};

