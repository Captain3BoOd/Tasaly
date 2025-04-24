#pragma once

#include "Core.h"

#include "Window.h"
#include "Tasaly/LayerStack.h"
#include "Tasaly/Events/Event.h"
#include "Tasaly/Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}