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
