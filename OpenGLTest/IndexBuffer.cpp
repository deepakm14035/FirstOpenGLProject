
#include "IndexBuffer.h"
#include "renderer.h"
#include <GLEW/glew.h>
#include <iostream>
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    :m_Count(count){
    if (sizeof(unsigned int) != sizeof(GLuint)) {
        std::cout << "error: size mismatch" << std::endl;
        return;
    }
    GLCALL(glGenBuffers(1, &m_RendererId));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));//copying vertices variable into vRAM
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}