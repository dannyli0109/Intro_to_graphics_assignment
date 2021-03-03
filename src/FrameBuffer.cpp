#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
{
	Create(width, height);
}

void FrameBuffer::Create(int width, int height)
{
	if (exists)
	{
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(1, &texID);
	}
	exists = true;

	glGenFramebuffers(1, &fboID);
	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, fboID);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texID, 0);


	glGenRenderbuffers(1, &rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "All is well!" << std::endl;
	}
	else
	{
		std::cout << "All is despair!" << std::endl;
		exists = false;
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(1, &texID);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	if (exists)
	{
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(1, &texID);
	}
}

FrameBuffer::FrameBuffer(FrameBuffer&& other)
{
	if (&other == this)
	{
		return;
	}

	this->fboID = other.fboID;
	this->texID = other.texID;

	this->exists = other.exists;

	other.exists = false;

}

const FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other)
{
	if (&other == this)
	{
		return *this;
	}

	if (exists)
	{
		glDeleteFramebuffers(1, &fboID);
		glDeleteTextures(1, &texID);
		glDeleteRenderbuffers(1, &rboID);
	}


	this->fboID = other.fboID;
	this->texID = other.texID;

	this->exists = other.exists;

	other.exists = false;

	return *this;
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindTexture(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texID);
}

