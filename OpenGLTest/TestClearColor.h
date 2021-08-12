#pragma once
#include "test.h"

namespace Testing {

	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime);
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_Color[4];
	};
}