#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "..\ShaderLoader\ShaderLoader.h"
#include <string>
#include "..\Texture\Texture.h"

/**
* Sprite has its x,y,w,h that defines its position and size on the screen.
* By providing image path of JPG or PNG in constructor, that image will be used as texture when rendering sprite
*/
class Sprite
{
public:
	float w, h;
	float x, y;
	int layer;
private:
	unsigned int vertexBufferID, indexBufferID;
	float vertexData[16];
	/**
	* Sets index data that will be used for every future texture.
	*/
	static unsigned int indexData[6];
	unsigned int shader;
	Texture* texture;


public:
	Sprite();

	/**
	* Creates texture from given PNG/JPG image file path
	* Generates vertex buffer and index buffer
	* Updates vertex data with passed x, y, w and h values. Vertex buffer and index buffer needs to be generated before this step.
	* Binds buffer GL_ARRAY_BUFFER to generated vertexBufferID and defines it's vertex data
	* Binds buffer GL_ELEMENT_ARRAY_BUFFER to generated indexBufferID and defines it's index data
	* Reads shader source and compiles it, generates shader program ID, binds compiled shader to shader program and uses it
	*/
	Sprite(float w, float h, float x, float y, std::string path);

	/**
	* Deletes configured shader.
	*/
	~Sprite();



	/**
	* Binds previously generated and configured vertexBufferID.
	* Binds previously generated and configured indexBufferID.
	* Select previously configured shader.
	* Configures vertex attrib pointer for position vertices and for texture UV vertices.
	* Draws previously configured and binded vertex/index data
	*/
	void Render();

	/**
	* Sets x and y values and updates vertex data with new values
	*/
	void SetPosition(float x, float y);

	/**
	* Sets w and h values and updates vertex data with new values
	*/
	void SetSize(float w, float h);


private:

	/**
	* Updates vertex data.
	* Updates 8(4*2) position vertices with current values of x, y, w, h and 8(4*2) UV vertices with current values of x, y, w, h.
	* Updates 8(4*2) UV vertices -> maps them to position vertices.
	* Binds vertexBufferID and sets it's data to vertexData
	*/
	void UpdateVertexData();

};

