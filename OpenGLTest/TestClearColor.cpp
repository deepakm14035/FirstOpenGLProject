
#include "TestClearColor.h"
#include "renderer.h"
#include "imgui/imgui.h"
namespace Testing {
	TestClearColor::TestClearColor() :m_Color{1.0f, 0.0f, 1.0f, 1.0f}
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}
	void TestClearColor::OnRender()
	{
		GLCALL(glClearColor( m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color",m_Color);
	}
}