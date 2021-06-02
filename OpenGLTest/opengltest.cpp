#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderSourceCode {
    std::string vertexShader;
    std::string fragmentShader;
};

ShaderSourceCode readShaderFile(const std::string& path) {
    std::ifstream stream(path);

    enum class ShaderType {
        NONE = -1, Vertex = 0, Fragment = 1
    };

    std::string line;
    std::stringstream str[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            }
            else {
                type = ShaderType::Fragment;
            }
        }
        else {
            str[(int)type] << line<<"\n";
        }
    }
    return { str[0].str(),str[1].str() };
}


unsigned int CompileShader(const int type, const std::string& shaderCode) {
    unsigned int id = glCreateShader(type);
    const char* src = &shaderCode[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
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

    float vertices[8] = { 
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    //unsigned int buffer;
    VertexBuffer vbo(vertices,4*2*sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//specifies details for first attribute to be passed to vertex shader
    //http://docs.gl/gl4/glVertexAttribPointer

    //unsigned int indexBufferObj;
    //glGenBuffers(1, &indexBufferObj);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);//copying vertices variable into vRAM
    IndexBuffer ibo(indices, (unsigned int)6);
    ShaderSourceCode ssc= readShaderFile("res/shader/firstShader.shader");
    std::cout << ssc.vertexShader << std::endl;
    int programId = createProgram(ssc.vertexShader, ssc.fragmentShader);
    glUseProgram(programId);
    int uniformVarId=glGetUniformLocation(programId,"u_Color");
    glUniform4f(uniformVarId, 0.2, 0.9, 0.8, 1.0);
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

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        GLCALL( glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}