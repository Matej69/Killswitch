#include "Sprite.h"


unsigned int Sprite::indexData[6] = {
	0, 1, 2,
	2, 3, 0
};


Sprite::Sprite()
{
	
}

Sprite::Sprite(float w, float h, float x, float y) : w(w), h(h), x(x), y(y)
{
	this->UpdateVertexData();

	glGenBuffers(1, &this->vertexDataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), this->vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &this->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), Sprite::indexData, GL_STATIC_DRAW);

	ShaderSources shaderSources = ShaderLoader::ParseShader("res/shaders/basic.shader");
	this->shader = ShaderLoader::CreateShader(shaderSources.vertex, shaderSources.fragment);
	glUseProgram(this->shader);
}

Sprite::~Sprite()
{
	glDeleteProgram(this->shader);
}



void Sprite::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	UpdateVertexData();
}

void Sprite::SetSize(float w, float h)
{
	this->w = w;
	this->h = h;
	UpdateVertexData();
}

void Sprite::UpdateVertexData()
{
	this->vertexData[0] = x - w / 2;	this->vertexData[1] = y - h / 2;	this->vertexData[2] = 0.0f;		this->vertexData[3] = 0.0f;
	this->vertexData[4] = x + w / 2;	this->vertexData[5] = y - h / 2;	this->vertexData[6] = 1.0f;		this->vertexData[7] = 0.0f;
	this->vertexData[8] = x + w / 2;	this->vertexData[9] = y + h / 2;	this->vertexData[10] = 1.0f;	this->vertexData[11] = 1.0f;
	this->vertexData[12] = x - w / 2;	this->vertexData[13] = y + h / 2;	this->vertexData[14] = 0.0f;	this->vertexData[15] = 1.0f;
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), this->vertexData, GL_STATIC_DRAW);
}


void Sprite::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexDataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glUseProgram(this->shader);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)) );
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
