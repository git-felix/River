#pragma once
#include <string>

// openGL
#include <GL/glew.h>

// STB image
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class Texture
{
public:
	Texture(const std::string& path) :
		m_filePath(path), m_localBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_localBuffer)
		{
			stbi_image_free(m_localBuffer);
		}
	}

	~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void Bind(int slot)const
	{
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Unbind()const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int GetWidth() const
	{
		return m_Width;
	}
	int GetHeight() const
	{
		return m_Height;
	}
	unsigned char* get_local_buffer() const
	{
		return m_localBuffer;
	}

private:
	GLuint m_textureID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_Width, m_Height, m_BPP;
};