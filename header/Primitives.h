#pragma once
#include<string>
#include<vector>

#include<glew.h>
#include<glfw3.h>

#include "Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive();
	~Primitive();

	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices);
	Vertex* getVertices();
	GLuint* getIndices();
	const unsigned getnrOfVertices();
	const unsigned getnrOfIndices();

};

class Quad : public Primitive {
public:
	Quad();
	~Quad();
private:
};

class Triangle : public Primitive {
public:
	Triangle();
	~Triangle();
private:
};

class Pyramid : public Primitive {
public:
	Pyramid();
	~Pyramid();
private:
};