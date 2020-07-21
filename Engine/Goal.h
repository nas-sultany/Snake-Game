#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>

class Goal {
public:
	Goal(std::mt19937& rng, const Board& gameboard, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& gameboard, const Snake& snake);
	void Draw(Board& gameboard) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Blue;
	Location loc;
};