#pragma once

#include "Core.h"

#include "Window.h"
#include "Tasaly/LayerStack.h"
#include "Tasaly/Events/Event.h"
#include "Tasaly/Events/ApplicationEvent.h"

#include "Tasaly/ImGui/ImGuiLayer.h"

#include "Tasaly/Renderer/VertexArray.h"
#include "Tasaly/Renderer/Shader.h"
#include "Tasaly/Renderer/Buffer.h"

#include "Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_SquareShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
