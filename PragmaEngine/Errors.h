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
#pragma once	//This file holds some global error functions

#include <string>
#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace PragmaEngine {

	extern void fatalError(std::string errorString);
	/* extern void fatalerrorTest(std::string errorString); */
}