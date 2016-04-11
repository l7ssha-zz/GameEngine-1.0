#include "Window.h"

namespace PragmaEngine {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::createWindow(std::string windowName, int windowHeight, int windowWidth, unsigned int flag)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (flag & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (flag & FULLSCREN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (flag & BORDER)
			flags |= SDL_WINDOW_BORDERLESS;

		//Open an SDL window
		_sdlwindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);
		if (_sdlwindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		//Set up our OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlwindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}

		//Set up glew (optional but recommended)
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}

		std::cout << "*** OpenGL Version: " << glGetString(GL_VERSION) << " ***\n" << std::endl;

		//Set the background color to blue
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		//Swap our buffer and draw everything to the screen!
		SDL_GL_SwapWindow(_sdlwindow);
	}

	void Window::WindowAtributes(bool doublebuffer, bool SwapInterval)
	{
		//Tell SDL that we want a double buffered window so we dont get
		//any flickering
		if (doublebuffer == false)
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
		else
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


		if (SwapInterval == false)
			SDL_GL_SetSwapInterval(0);
		else
			SDL_GL_SetSwapInterval(1);
	}

}