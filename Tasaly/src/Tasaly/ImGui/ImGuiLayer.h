#pragma once

#include "Tasaly/Layer.h"
#include "Tasaly/Events/Event.h"
#include "Tasaly/Events/KeyEvent.h"
#include "Tasaly/Events/MouseEvent.h"
#include "Tasaly/Events/ApplicationEvent.h"

namespace Tasaly {

	class TASALY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	private:
		float m_Time = 0.0f;
	};

}
