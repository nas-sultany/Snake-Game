/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	gameboard(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	goal(rng, gameboard, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!TitleScreen) {



		if (!GameOver) {


			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				delta = { 0,-1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				delta = { 0,1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				delta = { -1,0 };
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				delta = { 1,0 };
			}


			++snakeMoveCounter;
			if (snakeMoveCounter >= snakeMovePeriod) {
				snakeMoveCounter = 0;
				const Location next = snake.GetNextHeadLocation(delta);
				if (!gameboard.IsInsideBoard(next) || snake.SegmentInTile(next, false)) { // check if snake is going off board or will collide with itself (exclude tail)
					GameOver = true;
				}
				else {
					const bool targetReached = (next == goal.GetLocation());
					if (targetReached) { // snake reaches target
						snake.Append();	// grow snake

					}
					snake.MoveBy(delta);
					if (targetReached) {
						goal.Respawn(rng, gameboard, snake);	// respawn goal after snake moves
					}
				}

			}
		}
	}
	else {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			TitleScreen = false;
		}
	}
}

void Game::ComposeFrame()
{
	if (TitleScreen) {
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
	else {


		gameboard.DrawBorder();
		snake.Draw(gameboard);
		goal.Draw(gameboard);
		if (GameOver) {
			SpriteCodex::DrawGameOver(200, 200, gfx);
		}
	}
}
