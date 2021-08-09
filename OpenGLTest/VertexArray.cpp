#include "VertexArray.h"
#include "renderer.h"
#include "VertexBufferLayout.h"
#include <iostream>

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	((VertexBuffer&)vb).Bind();
	const auto& arr=layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < arr.size(); i++) {
		GLCALL( glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, arr[i].size, arr[i].type, arr[i].normalized,
			layout.getStride() , (const void*)offset));//specifies details for first attribute to be passed to vertex shader
		offset += VertexBufferElement::getSizeOfType(arr[i].type) * arr[i].size;
	}
}

void VertexArray::Bind() const
{
	//std::cout << m_RendererId << std::endl;
	GLCALL( glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind() const
{
	GLCALL(glBindVertexArray(0));
}
