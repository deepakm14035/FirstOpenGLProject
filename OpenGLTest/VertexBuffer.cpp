#include "VertexBuffer.h"
#include "renderer.h"
#include <GLEW/glew.h>
VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    GLCALL(glGenBuffers(1, &m_RendererId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//copying vertices variable into vRAM
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}