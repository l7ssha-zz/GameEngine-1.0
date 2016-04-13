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

#include <glm/glm.hpp>
#include <PragmaEngine/SpriteBatch.h>
#include <PragmaEngine/ResourceManager.h>

class Bullet
{
public:
    Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
    ~Bullet();

    void draw(PragmaEngine::SpriteBatch& spriteBatch);
    // Returns true when we are out of life
    bool update();

private:
    int _lifeTime;
    float _speed;
    glm::vec2 _direction;
    glm::vec2 _position;
};

