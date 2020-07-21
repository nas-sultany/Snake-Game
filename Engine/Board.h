#pragma once
#include "Graphics.h"
#include "Location.h"
#

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth() const {
		return width;
	}
	int GetGridHeight() const {
		return height;
	}
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int dimension = 20; // cells are 20x20
	static constexpr int width = 30;
	static constexpr int height = 25;
	Graphics& gfx;
	// Offsets to center grid on screen
	const int offset_x = (gfx.ScreenWidth - width * dimension) / 2;
	const int offset_y = (gfx.ScreenHeight - height * dimension) / 2;
};