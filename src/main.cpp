#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Game.h"

using namespace std;

int main() {
	// Create game object and let it run
	Game game;
	game.mainLoop();

	// Tells the system to terminate program
	return 0;
}