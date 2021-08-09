#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    glLogCall(#x, __FILE__, __LINE__);


void GLClearError();

bool glLogCall(const char* func, const char* filename, int lineNo);

class Renderer {
public:
    //Renderer();
    void draw(const VertexArray& va, const IndexBuffer& ibo, const Shader& shader) const;
    void clear() const;
};