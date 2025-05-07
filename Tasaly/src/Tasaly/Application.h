#pragma once

#include "Core.h"

#include "Window.h"
#include "Tasaly/LayerStack.h"
#include "Tasaly/Events/Event.h"
#include "Tasaly/Events/ApplicationEvent.h"

#include "Tasaly/ImGui/ImGuiLayer.h"

namespace Tasaly {

	class TASALY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
