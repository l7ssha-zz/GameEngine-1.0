#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(NATIVE_WITDH),
	_screenHeight(NATIVE_HEIGHT),
	_time(0.0f),
	_gameState(GameState::PLAY)
{

}

//Destructor
MainGame::~MainGame()
{
}

//This runs the game
void MainGame::run() {
	initSystems();

	//Initialize our sprites. (temporary)
	_sprites.push_back(new PragmaEngine::Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new PragmaEngine::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	//This only returns when the game ends
	gameLoop();
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {

	_window.createWindow("Game Window", 600, 800, 0);	//create window

	_window.WindowAtributes(); //Tell SDL that we want a double buffered window so we dont get any flickering

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

//This is the main game loop for our program
void MainGame::gameLoop() {

	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {
		//Used for frame time measuring
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01;
		drawGame();
		calculateFPS();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 80) {
			std::cout << floor(_fps) << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		//Limit the FPS to the max FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
		}
	}
}

//Processes input with SDL
void MainGame::processInput() {
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {

	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable the shader
	_colorProgram.use();

	//We are using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Get the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set the constantly changing time variable
	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Draw our sprite!
	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//disable the shader
	_colorProgram.unuse();

	//Swap our buffer and draw everything to the screen!
	_window.swapBuffer();
}

void MainGame::calculateFPS() {
	//The number of frames to average
	static const int NUM_SAMPLES = 10;
	//Stores all the frametimes for each frame that we will average
	static float frameTimes[NUM_SAMPLES];
	//The current frame we are on
	static int currentFrame = 0;
	//the ticks of the previous frame
	static float prevTicks = SDL_GetTicks();

	//Ticks for the current frame
	float currentTicks = SDL_GetTicks();

	//Calculate the number of ticks (ms) for this frame
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	//current ticks is now previous ticks
	prevTicks = currentTicks;

	//The number of frames to average
	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	//Average all the frame times
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	//Calculate FPS
	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	}
	else {
		_fps = 60.0f;
	}


}