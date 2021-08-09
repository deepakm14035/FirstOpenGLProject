#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();//GLEW gives header files to functions in graphics card in system

    float vertices[18] = { 
        100.0f,100.0f,0.0f,0.0f,
        200.0f,100.0f,1.0f,0.0f,
        200.0f,200.0f,1.0f,1.0f,
        100.0f,200.0f,0.0f,1.0f
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    
    //GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    //unsigned int buffer;
    VertexArray va;
    VertexBuffer vbo(vertices,4*4*sizeof(float));//4 floats per vertex

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);//each vertex now contains texture sampling location
    va.AddBuffer(vbo, layout);

    //http://docs.gl/gl4/glVertexAttribPointer

    //unsigned int indexBufferObj;
    //glGenBuffers(1, &indexBufferObj);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);//copying vertices variable into vRAM
    IndexBuffer ibo(indices, (unsigned int)6);
    glm::mat4 proj = glm::ortho(0.0f,960.0f,0.0f,540.0f,0.0f,1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100,0,0));

    //glm::mat4 mvp = proj * view;

    Shader shader("res/shader/firstShader.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2, 0.9, 0.8, 1.0);
    //shader.SetUniformMat4f("u_MVP", proj);
    Texture texture("res/images/UpgradeIcon.png");
    texture.bind();
    shader.SetUniform1i("u_texture",0);

    ibo.Unbind();
    va.Unbind();
    shader.Unbind();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    float colorVal = 0;
    Renderer renderer;
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glm::vec3 translationA(100.0f, 0.0f, 0.0f);
    glm::vec3 translationB(300.0f, 0.0f, 0.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);
        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5,-0.5);
        glVertex2f(0, 0.5);
        glVertex2f(0.5, -0.5);
        glEnd();*/
        //va.Bind();
        //ibo.Bind();
        //shader.Bind();
        renderer.clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat3("floatA", &translationA.x, 0.0f, 1000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("floatB", &translationB.x, 0.0f, 1000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            view = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ibo, shader);

            view = glm::translate(glm::mat4(1.0f), translationB);
            mvp = proj * view;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ibo, shader);

            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                //counter++;
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        renderer.draw(va, ibo, shader);
        colorVal += 0.001;
        if (colorVal > 1.0f)
            colorVal = 0.0f;
        shader.SetUniform4f("u_Color", 0.2, 1.0f - colorVal, colorVal, 1.0);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //GLCALL( glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0));

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers 
        GLFW windows are by default double buffered. That means that you have two rendering buffers; 
        a front buffer and a back buffer. The front buffer is the one being displayed and the back buffer 
        the one you render to.
        When the entire frame has been rendered, it is time to swap the back and the front buffers in 
        order to display what has been rendered and begin rendering a new frame. This is done with 
        glfwSwapBuffers.*/
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}