#pragma once
#include "Graphics.h"
#include <iostream>

class Texture
{
public:
	/**
	 * Load texture from an image file.
	 * 
	 * \param filename for the image texture
	 */
	Texture(std::string filename);
	~Texture();
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetChannels() { return channels; }
	std::string GetName();
	void SetName(std::string name);
	void Bind(int textureUnit);
	static void Unbind();
	GLuint& GetId();
private:
	int width;
	int height;
	int channels;
	GLuint textureID;
	std::string name = "";
};

