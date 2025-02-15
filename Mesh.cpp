#pragma once

#include "Mesh.h"

#include "libs.h"

void Mesh::initVAO()
{

    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);


    //generate vbo (vertex buffer object) and bind and send data
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //vbo is bound to attached point GL array buffer
    //GL_STATIC_DRAW - when you dont want top change it
    //GL_DYBNAMIC_DRAW - when you want to change it dynamically
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);  //data we send to graphics card

    //generate ebo (element buffer object)
    if (this->nrOfIndices > 0) {
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
    }

    //this above is costly, so you want to only do this once
    //now enable vertex attribute pointers - so graphics card knows which floats are for position, color, and text coord
    //this is input assembly, we tell the graphics card how to use data here
    //not normalized, stride is length of data, how much is there memory to the next attribute for offset

    //GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0); //0 and 0 for first param for both of these

    //color 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    //texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    //normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    //unbind now
    glBindVertexArray(0);
}


void Mesh::updateUniforms(Shader* shader)
{
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::updateModelMatrix()
{
    this->ModelMatrix = glm::mat4(1.f);
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));//with last, choosing which axis to rotate (x,y,z)
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale); //1 is original scale
}

//constructor with normal data
Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices,
    glm::vec3 position,glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale)
{
    //order important here
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;

    this->nrOfVertices = nrOfVertices;
    this->nrOfIndices = nrOfIndices;

    this->vertexArray = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < nrOfVertices; i++) {
        this->vertexArray[i] = vertexArray[i];
    }
    this->indexArray = new GLuint[this->nrOfIndices];
    for (size_t i = 0; i < nrOfIndices; i++) {
        this->indexArray[i] = indexArray[i];
    }

	this->initVAO();
	this->updateModelMatrix();
}
//constructor with primitive
Mesh::Mesh(Primitive* primitive,
    glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale)
{
    //order important here
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;

    this->nrOfVertices = primitive->getnrOfVertices();
    this->nrOfIndices = primitive->getnrOfIndices();

    //TODO make this more efficient
    this->vertexArray = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < this->nrOfVertices; i++) {
        this->vertexArray[i] = primitive->getVertices()[i];
    }
    this->indexArray = new GLuint[this->nrOfIndices];
    for (size_t i = 0; i < this->nrOfIndices; i++) {
        this->indexArray[i] = primitive->getIndices()[i];
    }

    this->initVAO();
    this->updateModelMatrix();
}

Mesh::Mesh(const Mesh& obj)
{
    //order important here
    this->position = obj.position;
    this->origin = obj.origin;
    this->rotation = obj.rotation;
    this->scale = obj.scale;

    this->nrOfVertices = obj.nrOfVertices;
    this->nrOfIndices = obj.nrOfIndices;

    //TODO make this more efficient
    this->vertexArray = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < this->nrOfVertices; i++) {
        this->vertexArray[i] = obj.vertexArray[i];
    }
    this->indexArray = new GLuint[this->nrOfIndices];
    for (size_t i = 0; i < this->nrOfIndices; i++) {
        this->indexArray[i] = obj.indexArray[i];
    }

    this->initVAO();
    this->updateModelMatrix();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    if (this->nrOfIndices > 0) {
        glDeleteBuffers(1, &this->EBO);
    }
    delete[] this->vertexArray;
    delete[] this->indexArray;
}

void Mesh::setPosition(const glm::vec3 pos)
{
    this->position = pos;
}

void Mesh::setOrigin(const glm::vec3 origin)
{
    this->origin = origin;
}

void Mesh::setRotation(const glm::vec3 rotation)
{
    this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 scale)
{
    this->scale = scale;
}

void Mesh::Rotate(const glm::vec3 rotation)
{
    this->rotation += rotation;
}


void Mesh::Move(const glm::vec3 pos)
{
    this->position += pos;
}

void Mesh::Scale(const glm::vec3 scale)
{
    this->scale += scale;
}

void Mesh::update()
{
}

void Mesh::render(Shader* shader)
{
    //update uniforms
    this->updateModelMatrix();
    this->updateUniforms(shader);
    //bind vertex array object
    //when you update uniforms you unbind shader, so use the shader to rebind
    shader->use();
    glBindVertexArray(this->VAO);

    //draw
    if (this->nrOfIndices==0) {
        glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
    }
    else {
        glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
    }

    //cleanup
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
