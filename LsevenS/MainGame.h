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

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <PragmaEngine\GLSLProgram.h>
#include <PragmaEngine\GLTexture.h>
#include <PragmaEngine\Sprite.h>
#include <PragmaEngine\Errors.h>

#include <PragmaEngine\Engine.h>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

	void calculateFPS();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

	std::vector <Sprite*> _sprites;
    Sprite _sprite;

    GLSLProgram _colorProgram;
    //GLTexture _playerTexture;

    float _time;

	float _frameTime;
	float _fps;
	float _maxFPS = 400.0f;
};

