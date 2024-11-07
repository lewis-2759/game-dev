#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Vertex.h"

static std::vector<Vertex> loadOBJ(const char* fileName) {

	//Vertex
	std::vector <glm::fvec3>  vertex_positions;
	std::vector <glm::fvec3>  vertex_normals;
	std::vector <glm::fvec2>  vertex_texcoords;

	//face 
	std::vector <GLint> vertex_positions_indices;
	std::vector <GLint> vertex_normals_indices;
	std::vector <GLint> vertex_texcoords_indices;

	//end result vertices
	std::vector<Vertex> vertices;

	//temp for getting data
	std::stringstream ss;
	std::ifstream in_file(fileName);
	std::string line = "";
	std::string prefix = "";

	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint;

	if (!in_file.is_open()) {
		throw "ERROR::OBJLOADER COULD NOT OPEN FILE";
	}
	//getting lines
	while (std::getline(in_file, line)) {
		ss.clear();
		//get prefix of line
		ss.str(line);
		ss >> prefix;

		if (prefix == "#") {	//ignore

		}
		else if (prefix == "o") {

		}
		else if (prefix == "s") {

		}
		else if (prefix == "use_mtl") {	//ignore

		}
		else if (prefix == "v") {	//vertex position
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt") {	//vertex texcoords
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn") {	//vertex normals
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f") {
			int counter = 0;
			while (ss >> temp_glint) {
				//putting indices in correct array
				if (counter == 0) {
					vertex_positions_indices.push_back(temp_glint);
				}
				else if (counter == 1) {
					vertex_texcoords_indices.push_back(temp_glint);
				}
				else if (counter == 2) {
					vertex_normals_indices.push_back(temp_glint);
				}

				//handling characters
				if (ss.peek() == '/') {
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ') {
					++counter;
					ss.ignore(1, ' ');
				}

				//reset counter after 
				if (counter > 2) {
					counter = 0;
				}
			}
		}
	}//end while
	
		//build final vertex array (mesh)
		vertices.resize(vertex_positions_indices.size(), Vertex());

		//load in all indices
		for (size_t i = 0; i < vertices.size(); i++) {
			vertices[i].position = vertex_positions[vertex_positions_indices[i ]-1];
			vertices[i].texcoord = vertex_texcoords[vertex_texcoords_indices[i]-1];
			vertices[i].normal = vertex_normals[vertex_normals_indices[i]-1];
			vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
		}
		//debug
		std::cout << line << "\n";
		std::cout << "number of vertices:" << vertices.size() << "\n";

	return vertices;
}