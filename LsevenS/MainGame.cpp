#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(NATIVE_WITDH),
	_screenHeight(NATIVE_HEIGHT),
	_time(0.0f),
	_gameState(GameState::PLAY)
{
	_camera2d.init(_screenWidth, _screenHeight);
}

//Destructor
MainGame::~MainGame()
{
}

//This runs the game
void MainGame::run() {
	initSystems();

	/*
	//Initialize our sprites. (temporary)
	_sprites.push_back(new PragmaEngine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new PragmaEngine::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	*/
	//This only returns when the game ends

	gameLoop();
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {

	_window.createWindow("Game Window", 600, 800, 0);	//create window
	_window.WindowAtributes(); //Tell SDL that we want a double buffered window so we dont get any flickering

	_spriteBatch.init();

	initShaders();

	_FPSLimiter.init(_maxFPS);
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

		_FPSLimiter.begin();

		processInput();
		_time += 0.1;

		_camera2d.update();

		drawGame();

		_fps = _FPSLimiter.end();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

//Processes input with SDL
void MainGame::processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.SetMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
		_camera2d.setPosition(_camera2d.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_s))
		_camera2d.setPosition(_camera2d.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	if (_inputManager.isKeyPressed(SDLK_a))
		_camera2d.setPosition(_camera2d.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_d))
		_camera2d.setPosition(_camera2d.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	if (_inputManager.isKeyPressed(SDLK_q))
		_camera2d.setScale(_camera2d.getScale() + SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDLK_e))
		_camera2d.setScale(_camera2d.getScale() - SCALE_SPEED);
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCords = _inputManager.getMouseCoords();
		mouseCords = _camera2d.convertScreenToWorld(mouseCords);
		std::cout << "x: " << mouseCords.x << " " << "y: " << mouseCords.y << std::endl;
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

	//Set the camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2d.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static PragmaEngine::GLTexture texture = PragmaEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	PragmaEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

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
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	//Average all the frame times
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];
	frameTimeAverage /= count;

	//Calculate FPS
	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;


}