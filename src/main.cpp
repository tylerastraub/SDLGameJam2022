#include "GameLoop.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* args[]) {
    GameLoop game;
	if(game.init()) {
		game.startLoop();
	}

	SDL_Quit();

    return 0;
}