#include <functional>
#include <sstream>

#include <Tasaly.h>

#include "imgui/imgui.h"

class ExampleLayer : public Tasaly::Layer
{
public:
	ExampleLayer():
		Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Tasaly::Input::IsKeyPressed(TS_KEY_TAB))
			TS_INFO("TAB key is pressed");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("ExampleLayer");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(Tasaly::Event& event) override
	{
		//TS_TRACE("{0}", event.ToString());
	}
};

class Sandbox: public Tasaly::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

private:

};

Tasaly::Application* Tasaly::CreateApplication()
{
	return new Sandbox();
}

