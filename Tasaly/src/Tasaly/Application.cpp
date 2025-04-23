#include "tspch.h"
#include "Application.h"

#include "Tasaly/Events/ApplicationEvent.h"
#include "Tasaly/Log.h"

namespace Tasaly {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}
