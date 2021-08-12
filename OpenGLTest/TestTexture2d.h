#pragma once
#include "test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
namespace Testing {

	class TestTexture2d : public Test {
	public:
		TestTexture2d();
		~TestTexture2d();

		void OnUpdate(float deltaTime);
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ibo;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		glm::mat4 m_proj;
		glm::mat4 m_view;
	};
}