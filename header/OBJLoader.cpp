#include "OBJLoader.h"


static std::vector<Vertex> loadOBJ(const char* fileName) {

	//Vertex
	std::vector <glm::fvec3>  vertex_position;
	std::vector <glm::fvec3>  vertex_normal;
	std::vector <glm::fvec2>  vertex_texcoord;

	//face 
	std::vector <GLint> vertex_position_indices;
	std::vector <GLint> vertex_normal_indices;
	std::vector <GLint> vertex_texcoord_indices;

	//end result vertices
	std::vector<Vertex> vertices;

	//temp for getting data
	std::stringstream ss;
	std::ifstream in_file(fileName);
	std::string line = "";

	if (!in_file.is_open()) {
		throw "ERROR::OBJLOADER COULD NOT OPEN FILE";
	}
	//getting lines
	while (std::getline(in_file, line)) {
		ss.str(line);



	}




	return vertices;
}