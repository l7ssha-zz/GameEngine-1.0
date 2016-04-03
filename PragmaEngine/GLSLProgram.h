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

#include "Errors.h"

#include <vector>
#include <fstream>
#include <string>
#include <GL\glew.h>


//This class handles the compilation, linking, and usage of a GLSL shader program.
class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);
    void linkShaders();
    void addAttribute(const std::string& attributeName);

    GLint getUniformLocation(const std::string& uniformName);

    void use();
    void unuse();
private:

    void compileShader(const std::string& filePath, GLuint id);

	int _numAttributes;

    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
};

