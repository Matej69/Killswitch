#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


/**
* Loads PNG or JPG image data, generates GL_TEXTURE_2D object and gives reference to it(texture ID), sets GL_TEXTURE_2D with loaded image data.
* Provides Bind() function for generated texture with image data so it can be used when needed
*/
class Texture
{
public:
	unsigned int textureID;
	unsigned char* textureBuffer;

public:
	Texture();

	/**
	* Takes path of image that needs to be loaded.
	* Generates texture ID, binds it to GL_TEXTURE_2D, loads image data, binds loaded image data to generated texture
	*/
	Texture(std::string &path);

	/**
	* Frees opengl texture data
	*/
	~Texture();

	/**
	* Takes slot that will be used.
	* Activates texture on GL_TEXTURE0 + slot and binds our previously loaded texture as GL_TEXTURE_2D
	*/
	void Bind(unsigned int slot);
};

