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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
