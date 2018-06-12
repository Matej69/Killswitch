#include <string>
#include <iostream>
#include "Texture.h"
#include "..\stbImage\stb_image.h"


Texture::Texture(std::string &path)
{
	std::string extension = path.substr(path.length() - 3);

	// generate opengl texture
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Load image data into buffer
	stbi_set_flip_vertically_on_load(1);
	int w = 100; int h = 100;
	int numOfChannels = (extension == "png") ? 4 : 3;
	textureBuffer = stbi_load(path.c_str(), &w, &h, &numOfChannels, numOfChannels);

	// Assign loaded image data to opengl texture object
	int iternalFormat = (extension == "png") ? GL_RGBA8 : GL_RGB;
	int format = (extension == "png") ? GL_RGB : GL_RGB;
	if(extension == "jpg")
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBuffer);
	else if (extension == "png")
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

	// free image data if image was loaded
	if (textureBuffer) 
	{
		stbi_image_free(textureBuffer);
	}
	else
	{
		std::cout << "ERROR loading image data [ " << path << "]\n";
	}
}

Texture::Texture()
{
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}


void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);

}
