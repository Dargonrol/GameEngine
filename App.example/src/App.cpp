#include <CoreInclude.h>
#include <iostream>

class TestApp : public Core::Application
{
public:
	TestApp()
	{

	}

	~TestApp()
	{

	}

};

Core::Application* Core::CreateApplication()
{
	return new TestApp();
}