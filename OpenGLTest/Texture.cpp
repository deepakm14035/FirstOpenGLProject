#include "Texture.h"
#include "src/vendor/stl_image/stl_image.h"
#include<GLEW/glew.h>
#include "renderer.h"
#include <iostream>

Texture::Texture(const std::string& filepath)
	:m_filePath(filepath),m_rendererID(0), m_buffer(nullptr), m_BPP(0),m_width(0),m_height(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(filepath.c_str(), &m_width,&m_height,&m_BPP,4);
	bool a = m_buffer != NULL;
	std::cout << "buffer-" << a << std::endl;
	GLCALL(glGenTextures(1, &m_rendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D,m_rendererID));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));

	if (m_buffer)
		stbi_image_free(m_buffer);

	GLCALL(glBindTexture(GL_TEXTURE_2D,0));
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

void Texture::bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0+slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getHeight() const
{
	return 0;
}

int Texture::getWidth() const
{
	return 0;
}
