#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int CompileShader(const int type, const std::string& shaderCode) {
    unsigned int id=glCreateShader(type);
    const char* src = &shaderCode[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length, &length, message);
        std::cout << "error in compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader. error-" << message << std::endl;
        return 0;
    }
    return id;

}

unsigned int createProgram(const std::string& vs, const std::string& fs) {
    unsigned int program = glCreateProgram();
    unsigned int vsShaderId = CompileShader(GL_VERTEX_SHADER, vs);
    unsigned int fsShaderId = CompileShader(GL_FRAGMENT_SHADER, fs);
    glAttachShader(program, vsShaderId);
    glAttachShader(program, fsShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vsShaderId);
    glDeleteShader(fsShaderId);
    return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();//GLEW gives header files to functions in graphics card in system
    
    float vertices[6] = {-0.5f,-0.5f,0.0f,0.5f,0.5f,-0.5f};

    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),vertices,GL_STATIC_DRAW);//copying vertices variable into vRAM
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);//specifies details for first attribute to be passed to vertex shader
    //http://docs.gl/gl4/glVertexAttribPointer

    std::string vs = "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;"
        "\n"
        "void main(){\n"
        "gl_Position=position;\n"
        "}";

    std::string fs = "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;"
        "\n"
        "void main(){\n"
        "color=vec4(1.0,0.0,0.0,1.0);"
        "}";

    int programId = createProgram(vs, fs);
    glUseProgram(programId);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5,-0.5);
        glVertex2f(0, 0.5);
        glVertex2f(0.5, -0.5);
        glEnd();*/

        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}