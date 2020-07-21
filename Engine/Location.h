#pragma once
#include "Graphics.h"

struct Location {
	int x;
	int y;
	bool operator==(const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
};