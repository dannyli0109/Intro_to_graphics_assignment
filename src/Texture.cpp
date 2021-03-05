#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

/**
 * Load texture from an image file.
 *
 * \param filename for the image texture
 */
Texture::Texture(std::string filename)
{
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (data)
	{
		if (channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "unknown texture type" << std::endl;
		}
	}
	else {
		std::cout << "Fail to load texture" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}


std::string Texture::GetName()
{
	return name;
}

void Texture::SetName(std::string name)
{
	this->name = name;
}

void Texture::Bind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint& Texture::GetId()
{
	return textureID;
}
