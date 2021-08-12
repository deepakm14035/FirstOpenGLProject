#pragma once
#include <functional>
#include "test.h"
#include <vector>
#include "imgui/imgui.h"

namespace Testing {
	TestMenu::TestMenu(Test*& currentTestPointer):m_currentTest(currentTestPointer)
	{
	}
	TestMenu::~TestMenu()
	{
	}
	void TestMenu::OnImGuiRender() {
		for (auto& button : m_tests) {
			if (ImGui::Button(button.first.c_str())) {
				m_currentTest = button.second();
			}
		}
	}
}