#define GLCALL(x) GLClearError();\
    x;\
    glLogCall(#x, __FILE__, __LINE__);


void GLClearError();

bool glLogCall(const char* func, const char* filename, int lineNo);