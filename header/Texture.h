#pragma once

#include<iostream>
#include<string>

#include<glew.h>
#include<glfw3.h>


#include<glm.hpp>
#include<SOIL2.h>
class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;


public:

	GLuint getId() const;
	void bind(const GLint texture_unit);
	void unbind();
	void loadFromFile(const char* fileName);
	Texture(const char* fileName, GLenum type);
	~Texture();

};

