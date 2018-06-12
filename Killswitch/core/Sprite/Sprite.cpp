#include "Sprite.h"

unsigned int Sprite::indexData[6] = {
	0, 1, 2,
	2, 3, 0
};


Sprite::Sprite()
{
	
}

Sprite::Sprite(float w, float h, float x, float y, std::string path) : w(w), h(h), x(x), y(y), texture(new Texture(path))
{
	glGenBuffers(1, &this->vertexBufferID);
	glGenBuffers(1, &this->indexBufferID);

	this->UpdateVertexData();

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), this->vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
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
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), this->vertexData, GL_STATIC_DRAW);
}

void Sprite::Render()
{
	texture->Bind(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
	glUseProgram(this->shader);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)) );
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
