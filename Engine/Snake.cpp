#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta)
{
	for (int i = nSegments - 1; i > 0; --i) {	// Process all segments except head (segments[0])
		segments[i].Follow(segments[i - 1]);	// Follow segment before current one
	}
	segments[0].MoveBy(delta);			// Move head by delta
}

Location Snake::GetNextHeadLocation(const Location & delta) const
{
	Location head = segments[0].GetLocation();	// get head location
	head.x += delta.x;			// Calculate next head location
	head.y += delta.y;
	return head;
}

void Snake::Append()
{
	if (nSegments < nSegmentsMax) {
		segments[nSegments].InitBody();
		nSegments++;

	}
}

void Snake::Draw(Board & gameboard) const
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(gameboard);
	}
}

bool Snake::SegmentInTile(const Location & tile, const bool& checkEnd) const
{
	if (!checkEnd) {
		for (int i = 0; i < nSegments - 1; i++) {	// exclude end of snake from test, because it will move
			if (segments[i].GetLocation() == tile) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int i = 0; i < nSegments; i++) {	// check end of snake (for goal spawning)
			if (segments[i].GetLocation() == tile) {
				return true;
			}
		}
		return false;
	}
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;		// initialize location of snake head
	c = Snake::headColor;	// Set segment color c to head color
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;	// initialize color of body segment
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;		// segments follow preceding segment
}

void Snake::Segment::MoveBy(const Location & delta)
{
	assert(abs(delta.x) + abs(delta.y) == 1);	// make sure snake only moves by one unit
	loc.x += delta.x;	// Move head segment by delta
	loc.y += delta.y;
}

void Snake::Segment::Draw(Board & gameboard) const
{
	gameboard.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
