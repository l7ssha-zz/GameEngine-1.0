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

#include <unordered_map>
#include <glm\glm.hpp>

namespace PragmaEngine {

	// Input manager stores a key map that maps SDL_Keys to booleans.
	// If the value in the key map is true, then the key is pressed.
	// Otherwise, it is released.
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void SetMouseCoords(float x, float y);

		bool isKeyPressed(unsigned int keyID);

		glm::vec2 getMouseCoords() const { return _mouseCoords; }
	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};

}