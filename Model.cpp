#include "Model.h"

void Model::updateUniforms()
{
}

Model::Model(glm::vec3 position, Material* material, Texture* Odif, Texture* Ospec, std::vector<Mesh*> meshes )
{
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = Odif;
	this->overrideTextureSpecular = Ospec;
	//hard copy the meshes
	for (auto* i : meshes) {
		this->meshes.push_back(new Mesh(*i));
	}
	//move it to position given
	for (auto& i : this->meshes) {
		i->Move(this->position);
		i->setOrigin(this->position);
	}
}

Model::Model(glm::vec3 position, Material* material, Texture* Odif, Texture* Ospec, const char* fileName)
{

	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = Odif;
	this->overrideTextureSpecular = Ospec;

	std::vector<Vertex> mesh = loadOBJ(fileName);
	this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)));

	//move it to position given
	for (auto& i : this->meshes) {
		i->Move(this->position);
		i->setOrigin(this->position);
	}
}

Model::~Model()
{
	//delete all meshes
	for (auto*& i : this->meshes) {
		delete i;
	}
}

void Model::rotate(const glm::vec3 rotation)
{
	for (auto& i : this->meshes) {
		i->Rotate(rotation);
	}
}

void Model::update()
{
}

void Model::render(Shader* shader)
{
	//update uniforms
	this->updateUniforms();

	//update uniforms
	this->material->sendToShader(*shader);

	//use a program
	shader->use();

	//draw
	for (auto& i : this->meshes) {
		//bind textures
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);
		i->render(shader);
	}
}
