/*
------------------------- GAME ENGINE BY L7SSHA | ALL RIGTS RESERVED -------------------------
PragamEngine version 1.0
Copyright (c) 2016 Szymon "l7ssha" Uglis

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to no one to use this software for any purpose,
including commercial application

------------------------- GAME ENGINE BY L7SSHA | ALL RIGTS RESERVED -------------------------
*/

#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include <cstdlib>
#include <iostream>

#include "Errors.h"

namespace PragmaEngine {

	enum WindowFlag { INVISIBLE = 0x1, FULLSCREN = 0x2, BORDER = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int createWindow(std::string windowName, int windowHeight, int windowWidth, unsigned int flag);
		void swapBuffer();
		void WindowAtributes(bool doublebuffer = false, bool SwapInterval = false);

		int GetWindowHeight() { return _windowHeight; }
		int GetWindowWitdh() { return _windowWidth; }
	private:
		SDL_Window* _sdlwindow;
		int _windowHeight, _windowWidth;
	};

}