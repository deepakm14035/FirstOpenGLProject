#pragma once
#include <string>

class Texture {
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_buffer;
	int m_height, m_width, m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();
	void bind(unsigned int slot=0) const;
	void unbind() const;

	int getHeight() const;
	int getWidth() const;

};