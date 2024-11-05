#pragma once
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Primitives.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 origin;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initVAO();
	void updateUniforms(Shader* shader);
	void updateModelMatrix();

public:
	//can send in position, rotation, and scale in constructor
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, 
		glm::vec3 position = glm::vec3(0.f), glm::vec3 origin = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	Mesh(Primitive* primitive,
		glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale);
	Mesh(const Mesh& obj);
	~Mesh();

	void setPosition(const glm::vec3 pos);
	void setRotation(const glm::vec3 rotation);
	void setScale(const glm::vec3 scale);
	void setOrigin(const glm::vec3 origin);

	void Rotate(const glm::vec3 rotation);
	void Move(const glm::vec3 pos);
	void Scale(const glm::vec3 scale);

	void update();
	void render(Shader* shader);
};

