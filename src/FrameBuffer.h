#pragma once
#include "Graphics.h"
#include <iostream>
class FrameBuffer
{

public:
	/**
	 * Frame buffer, instead of render the pixel onto the screen, we use frame buffer to do post processing and other effects.
	 * 
	 */
	FrameBuffer() {}
	FrameBuffer(int width, int height);
	void Create(int width, int height);

	~FrameBuffer();

	FrameBuffer(const FrameBuffer& other) = delete;
	FrameBuffer(FrameBuffer&& other);

	const FrameBuffer& operator=(const FrameBuffer& other) = delete;
	const FrameBuffer& operator=(FrameBuffer&& other);


	void Bind();
	void Destroy();

	static void Unbind();

	void BindTexture(int textureUnit = 0);

private:
	GLuint fboID;
	GLuint texID;
	//GLuint rboID;

	bool exists = false;
};

