#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() : 
    _screenWidth(NATIVE_WITDH),
    _screenHeight(NATIVE_HEIGHT),
    _time(0.0f),
    _window(nullptr), 
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

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    //_playerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    gameLoop();		//This only returns when the game ends
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {

    SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL

	//Open an SDL window
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);	//Set up our OpenGL context
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    GLenum error = glewInit();						 //Set up glew (optional but recommended)
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew!");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//Tell SDL that we want a double buffered window so we dont get any flickering

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);			//Set the background color to blue

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
        processInput();
        _time += 0.03;
        drawGame();
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

    glClearDepth(1.0);									//Set the base depth to 1.0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the color and depth buffer

    _colorProgram.use();								//Swap our buffer and draw everything to the screen!

	glActiveTexture(GL_TEXTURE0);						//We are using texture unit 0
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler"); //Get the uniform location
    glUniform1i(textureLocation, 0);					//Tell the shader that the texture is in texture unit 0

    //Set the constantly changing time variable
    GLint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

    glBindTexture(GL_TEXTURE_2D, 0);	//unbind the texture

    _colorProgram.unuse();				//disable the shader

    SDL_GL_SwapWindow(_window);			//Swap our buffer and draw everything to the screen!
}    