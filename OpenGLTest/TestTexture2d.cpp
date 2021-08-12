
#include "TestTexture2d.h"
#include "renderer.h"
#include "imgui/imgui.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace Testing {
	TestTexture2d::TestTexture2d(): m_translationA(100.0f,0.0f,0.0f), m_translationB(100.0f, 0.0f, 0.0f)
	{
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
        m_vao = std::make_unique<VertexArray>();
        m_vbo = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));//4 floats per vertex

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);//each vertex now contains texture sampling location
        m_vao->AddBuffer(*m_vbo, layout);

        //http://docs.gl/gl4/glVertexAttribPointer

        //unsigned int indexBufferObj;
        //glGenBuffers(1, &indexBufferObj);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);//copying vertices variable into vRAM
        m_ibo = std::make_unique<IndexBuffer>(indices, (unsigned int)6);
        m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

        //glm::mat4 mvp = proj * view;

        m_shader = std::make_unique<Shader>("res/shader/firstShader.shader");
        m_shader->SetUniform4f("u_Color", 0.2, 0.9, 0.8, 1.0);
        //shader.SetUniformMat4f("u_MVP", proj);
        m_texture = std::make_unique<Texture>("res/images/UpgradeIcon.png");
        m_shader->SetUniform1i("u_texture", 0);

	}
	TestTexture2d::~TestTexture2d()
	{
	}
	void TestTexture2d::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2d::OnRender()
	{
        Renderer renderer;
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        m_texture->bind();
        m_view = glm::translate(glm::mat4(1.0f), m_translationA);
        glm::mat4 mvp = m_proj * m_view;
        m_shader->SetUniformMat4f("u_MVP", mvp);
        renderer.draw(*m_vao, *m_ibo, *m_shader);

        m_view = glm::translate(glm::mat4(1.0f), m_translationB);
        mvp = m_proj * m_view;
        m_shader->SetUniformMat4f("u_MVP", mvp);
        renderer.draw(*m_vao, *m_ibo, *m_shader);
    }
	void TestTexture2d::OnImGuiRender()
	{
        ImGui::SliderFloat3("floatA", &m_translationA.x, 0.0f, 0.0f);
        ImGui::SliderFloat3("floatB", &m_translationB.x, 0.0f, 0.0f);
	}
}