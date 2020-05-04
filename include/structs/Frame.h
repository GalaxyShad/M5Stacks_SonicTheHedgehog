#pragma once
#include "Geometry.h"

struct Frame {
    IntRect rect;
    Vector2i offset = Vector2i(0, 0);

	Frame(IntRect _rect)
	{
		rect = _rect;
		offset = Vector2i(_rect.width / 2, _rect.height / 2);
	}

    Frame(IntRect _rect, Vector2i _offset):
        rect(_rect), offset(_offset) {}

   
};
