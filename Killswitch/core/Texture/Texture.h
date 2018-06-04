#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;


class Texture
{
private:
	unsigned int textureID;
	unsigned char* textureBuffer;

public:
	Texture(string &path);
	~Texture();
	void Bind(unsigned int slot);
};

