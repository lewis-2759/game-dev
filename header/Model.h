#pragma once

#include<glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Model {
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms();

public:

	Model(glm::vec3 position, Material* material, Texture* Odif, Texture* Ospec, std::vector<Mesh*> meshes);
	~Model();

	void rotate(const glm::vec3 rotation);

	void update();
	void render(Shader* shader);

};