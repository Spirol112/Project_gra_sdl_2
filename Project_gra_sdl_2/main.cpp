#include "SDL.h"
#include"Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frame_delay = 1000 / FPS;


	Uint32 frame_start{};
	int frame_time{};
	

	game = new Game();

	game->init("...Magic Dungeon...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);

	while (game->running())
	{
		frame_start = SDL_GetTicks();
		//start screen
		/*while (false)
		{

		}*/
		//game
		game->handel_events();
		game->update();
		game->render();

		frame_time = SDL_GetTicks() - frame_start;

		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);
		}
		

	}

	game->cleen();

	return 0;
}