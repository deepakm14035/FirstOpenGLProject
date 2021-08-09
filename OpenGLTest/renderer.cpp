#include <GLEW/glew.h>
#include <iostream>
#include "renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* func, const char* filename, int lineNo) {
    while (GLenum error = glGetError()) {
        std::cout << "[OPENGL error]" << error << "\n file-" << filename << "\n funcname-" << func << ":" << lineNo << std::endl;
        return true;
    }
    return false;
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ibo, const Shader& shader) const {
    va.Bind();
    ibo.Bind();
    shader.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}