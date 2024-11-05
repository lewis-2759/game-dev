#include "Primitives.h"

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}

void Primitive::set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
{
	for (size_t i = 0; i < nrOfVertices; i++) {
		this->vertices.push_back(vertices[i]);
	}

	for (size_t i = 0; i < nrOfIndices; i++) {
		this->indices.push_back(indices[i]);
	}
}

 Vertex* Primitive::getVertices()
{
	 return this->vertices.data();
}

 GLuint* Primitive::getIndices()
 {
	 return this->indices.data();
 }

 const unsigned Primitive::getnrOfVertices()
 {
	 return this->vertices.size();
 }

 const unsigned Primitive::getnrOfIndices()
 {
	 return this->indices.size();
 }

 Quad::Quad()
	 : Primitive()
 {	
	 Vertex vertices[] =
	 {
		 //position                          //color                         //texcoords             //normals
		 glm::vec3(-0.5f, 0.5f, 0.f),         glm::vec3(1.f, 1.f, 0.f),       glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 1.f),       glm::vec2(0.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),
		 glm::vec3(0.5f, 0.5f, 0.f),          glm::vec3(1.f, 1.f, 1.f),       glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f)


	 };

	 //passing a pointer of this can cause problems because size will be pointer
	 unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	 //tells how many indices are going to be in there, so we don't use duplicates (reusing verticies)
	 GLuint indices[] =
	 {
		 0,1,2, //triangle one
		 0,2,3   //triale two reusing with 0 and 2 which were base poitns for other triangle
	 };
	 unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	 this->set(vertices, nrOfVertices, indices, nrOfIndices);
 }

 Quad::~Quad()
 {
 }

 Triangle::Triangle()
	 : Primitive()
	 {
		 Vertex vertices[] =
		 {
			 //position									//color                         //texcoords             //normals
				 //triangle
			 glm::vec3(0.5f, 0.5f, 0.f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(0.5f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
			 glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(0.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),
			 glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),


		 };

		 //passing a pointer of this can cause problems because size will be pointer
		 unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		 //tells how many indices are going to be in there, so we don't use duplicates (reusing verticies)
		 GLuint indices[] =
		 {
			 0,1,2, //triangle one
		 };
		 unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		 this->set(vertices, nrOfVertices, indices, nrOfIndices);
 }

 Triangle::~Triangle()
 {
 }

 Pyramid::Pyramid() 
	 : Primitive()
 {
	 Vertex vertices[] =
	 {
		 //position									//color                         //texcoords             //normals
			 //triangle front
		glm::vec3(0.f, 0.5f, 0.f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(0.5f, 1.f),    glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(0.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(0.f, 0.f, 1.f),
		 //triangle left
		glm::vec3(0.f, 0.5f, 0.f),         glm::vec3(1.f, 1.f, 0.f),       glm::vec2(0.5f, 1.f),    glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),       glm::vec3(0.f, 0.f, 1.f),       glm::vec2(0.f, 0.f),     glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(-1.f, 0.f, 0.f),
		 //triangle back
		glm::vec3(0.f, 0.5f, 0.f),         glm::vec3(1.f, 1.f, 0.f),       glm::vec2(0.5f, 1.f),    glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.5f, -0.5f, -0.5f),       glm::vec3(0.f, 0.f, 1.f),       glm::vec2(0.f, 0.f),     glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(0.f, 0.f, -1.f),
		 //triangle right
		glm::vec3(0.f, 0.5f, 0.f),         glm::vec3(1.f, 1.f, 0.f),       glm::vec2(0.5f, 1.f),    glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.5f),       glm::vec3(0.f, 0.f, 1.f),       glm::vec2(0.f, 0.f),     glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f, 0.f),     glm::vec3(1.f, 0.f, 0.f)


	 };

	 //passing a pointer of this can cause problems because size will be pointer
	 unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	 this->set(vertices, nrOfVertices, nullptr, 0);
 }

 Pyramid::~Pyramid()
 {
 }
