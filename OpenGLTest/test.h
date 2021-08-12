#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
namespace Testing {

	class Test {
	public:
		Test(){}
		virtual ~Test(){}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(){}
		virtual void OnImGuiRender(){}
	};
	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();
		void OnUpdate(float deltaTime) {}
		virtual void OnImGuiRender();
		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "registering test " << name << std::endl;
			m_tests.push_back(std::make_pair(name, []() {return new T; }));
		}
	private:
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
		Test*& m_currentTest;
	};
}