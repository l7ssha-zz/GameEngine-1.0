#include "InputManager.h"

namespace PragmaEngine {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID) {
		// Here we are treating _keyMap as an associative array.
		// if keyID doesn't already exist in _keyMap, it will get added
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	void InputManager::SetMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		// We dont want to use the associative array approach here
		// because we don't want to create a key if it doesnt exist.
		// So we do it manually
		auto it = _keyMap.find(keyID);

		if (it != _keyMap.end())
			return it->second;	// Found the key
		else
			return false; // Didn't find the key
	}

}