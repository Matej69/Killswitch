#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "..\ShaderLoader\ShaderLoader.h"
#include <string>

class Sprite
{
public:
	float w, h;
	float x, y;
	int layer;
private:
	unsigned int vertexDataBuffer, indexBuffer;
	float vertexData[16];
	static unsigned int indexData[6];
	unsigned int shader;


public:
	Sprite();
	Sprite(float w, float h, float x, float y);
	~Sprite();

	void Render();
	void SetPosition(float x, float y);
	void SetSize(float w, float h);

private:
	void UpdateVertexData();

};

