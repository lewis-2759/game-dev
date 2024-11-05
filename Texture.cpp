#include "Texture.h"

GLuint Texture::getId() const
{
    return this->id;
}

//dynamically choose which texture to use
void Texture::bind(const GLint texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(this->type, this->id);
}

void Texture::unbind()
{
    glActiveTexture(0);
    glBindTexture(this->type, 0);
}

//to redefine texture
void Texture::loadFromFile(const char* fileName)
{
    if (this->id) {
        glDeleteTextures(1, &this->id);
    }
    unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    //dont have to activate it, just bind
    glGenTextures(1, &this->id);
    glBindTexture(this->type, this->id);

    //set gl options
    glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT); //S and T are names for x and y, S = x, T = y coord
    glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //can read at opengl.com about texture options
    glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //mag is magnification, min is minification

    if (image)
    {
        glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(this->type); //mipmap is smaller and bigger versions of texture so it can change with perspective
    }
    else {
        std::cerr << "ERROR::TEXTURE::LOADFROMFILE::texture loading failed: " << fileName << "\n";
    }

    glActiveTexture(0);
    SOIL_free_image_data(image);    //free data from SOIL, imporant
}

Texture::Texture(const char* fileName, GLenum type)
{
    this->type = type;
    unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    //dont have to activate it, just bind
    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);

    //set gl options
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT); //S and T are names for x and y, S = x, T = y coord
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //can read at opengl.com about texture options
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //mag is magnification, min is minification

    if (image)
    {
        glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(type); //mipmap is smaller and bigger versions of texture so it can change with perspective
    }
    else {
        std::cerr << "ERROR::TEXTURE::texture loading failed: " << fileName << "\n";
    }

    glActiveTexture(0);
    glBindTexture(type, 0); //unbind all textures at the end
    SOIL_free_image_data(image);    //free data from SOIL, imporant
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}
