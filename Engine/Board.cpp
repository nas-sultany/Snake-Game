#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	
	gfx.DrawRectDim(loc.x*dimension+offset_x+3, loc.y*dimension+offset_y+3, dimension-3, dimension-3, c);	// add 6px padding to cells and offset to center on screen
}

void Board::DrawBorder()
{
	// Left border
	gfx.DrawRect(offset_x, offset_y, offset_x+1, gfx.ScreenHeight - offset_y, Colors::White);
	// Top border
	gfx.DrawRect(offset_x, offset_y, gfx.ScreenWidth-offset_x, offset_y+1, Colors::White);
	// Right border
	gfx.DrawRect(gfx.ScreenWidth - offset_x, offset_y, gfx.ScreenWidth - offset_x + 1, gfx.ScreenHeight - offset_y, Colors::White);
	// Bottom border
	gfx.DrawRect(offset_x, gfx.ScreenHeight - offset_y, gfx.ScreenWidth - offset_x, gfx.ScreenHeight - offset_y + 1, Colors::White);

}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x>=0 && loc.x<width &&
		loc.y>=0 && loc.y<height;
}
