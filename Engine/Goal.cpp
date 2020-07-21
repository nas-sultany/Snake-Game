#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & gameboard, const Snake & snake)
{
	Respawn(rng, gameboard, snake);
}

void Goal::Respawn(std::mt19937 & rng, const Board & gameboard, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, gameboard.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, gameboard.GetGridHeight() - 1);
	Location newGoal;
	do {
		newGoal.x = xDist(rng);
		newGoal.y = yDist(rng);
	} while (snake.SegmentInTile(newGoal, true));	// generate new goals until goal is not in snake segments

	loc = newGoal;

}

void Goal::Draw(Board & gameboard) const
{
	gameboard.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
