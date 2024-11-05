#include "Camera.h"



void Camera::updateCameraVectors()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{
	this->ViewMatrix = glm::mat4(1.f);

	this->movementSpeed = 3.f;
	this->sensitivity = 10.f;

	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.f);
	this->up = worldUp;

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;

	this->updateCameraVectors();
}

Camera::~Camera()
{
}

const glm::mat4 Camera::getViewMatrix()
{
	this->updateCameraVectors();
	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}

const glm::vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
	this->updateMouseInput(dt, offsetX, offsetY);
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
	this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
	this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

	if (this->pitch > 80.f) {
		this->pitch = 80.f;
	}
	else if (this->pitch < -80.f) {
		this->pitch = -80.f;
	}
	if (this->yaw > 360.f || this->yaw < -360.f) {
		this->yaw = 0.f;
	}
}

void Camera::move(const float& dt, const int direction)
{
	switch (direction)
	{
	case FORWARD:

		this->position += this->front * this->movementSpeed * dt;
		break;

	case BACKWARD:

		this->position -= this->front * this->movementSpeed * dt;
		break;

	case LEFT:

		this->position -= this->right * this->movementSpeed * dt;
		break;

	case RIGHT:

		this->position += this->right * this->movementSpeed * dt;
		break;

	case UP:

		this->position += this->up * this->movementSpeed * dt;
		break;

	case DOWN:

		this->position -= this->up * this->movementSpeed * dt;
		break;

	default:

		break;
	}
}
