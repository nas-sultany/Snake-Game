#pragma once
#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& in_loc);		// Initialize snake location on board
		void InitBody();						// Add body segment
		void Follow(const Segment& next);		// Segment follows higher segment to move snake
		void MoveBy(const Location& delta);		// Move segment by delta value
		void Draw(Board& gameboard) const;		// Draw segment on board grid
		const Location& GetLocation() const;
	private:
		Location loc;	// location on grid of segment
		Color c;		// color of segment
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta);	// direction to move snake
	Location GetNextHeadLocation(const Location& delta) const;
	void Append();						// grow snake after eating
	void Draw(Board& gameboard) const;	// draw snake on board grid
	bool SegmentInTile(const Location& tile, const bool& checkEnd) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;	// how many segments currently exist
};