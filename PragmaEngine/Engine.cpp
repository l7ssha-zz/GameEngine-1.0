#include "Engine.h"

namespace PragmaEngine {

	int initEngine()
	{
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		return 0;
	}

}