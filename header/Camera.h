#pragma once
#include<iostream>

#include<glew.h>
#include<glfw3.h>


#include<glm.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\matrix_transform.hpp>

enum direction { FORWARD ,BACKWARD, LEFT, RIGHT, UP , DOWN };
class Camera
{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	//private functions
	void updateCameraVectors();

public:

	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
	~Camera();

	//acessors 
	const glm::mat4 getViewMatrix();

	const glm::vec3 getPosition();

	//functions
	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
	
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);

	void move(const float& dt, const int direction);

};