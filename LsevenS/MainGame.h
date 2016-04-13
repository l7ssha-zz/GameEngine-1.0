/*
------------------------- l7s BY L7SSHA | ALL RIGTS RESERVED -------------------------
l7s version 1.0
Copyright (c) 2016 Szymon "l7ssha" Uglis

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to no one to use this software for any purpose,
including commercial application

------------------------- l7s BY L7SSHA | ALL RIGTS RESERVED -------------------------
*/
#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <vector>

#include <PragmaEngine/Engine.h>
#include <PragmaEngine/GLSLProgram.h>
#include <PragmaEngine/GLTexture.h>
#include <PragmaEngine/Sprite.h>
#include <PragmaEngine/Window.h>
#include <PragmaEngine/InputManager.h>
#include <PragmaEngine/Timing.h>
#include <PragmaEngine/SpriteBatch.h>
#include <PragmaEngine/Camera2D.h>
#include <PragmaEngine/Errors.h>
#include <PragmaEngine/ResourceManager.h>

#include "Bullet.h"

enum class GameState {PLAY, EXIT};

//Our example game class, just for testing purposes right now
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

    PragmaEngine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

	PragmaEngine::GLSLProgram _colorProgram;
	PragmaEngine::Camera2D _camera;

	PragmaEngine::SpriteBatch _spriteBatch;

	PragmaEngine::InputManager _inputManager;
	PragmaEngine::FpsLimiter _fpsLimiter;

    std::vector<Bullet> _bullets;
    
    float _maxFPS = 400.0f;
    float _fps;
    float _time;
};

