#include "Game_Control.h"
#include "Utilities.h"

int Ball::speed = 0;
int Game::mode = 0;
bool Game::quit = false;
int Game::HighScore_1P = 0;
int Game::LimitScore_2P = 0;

int main()
{

	Game Pong;
	Pong.Start();


	return 0;
}