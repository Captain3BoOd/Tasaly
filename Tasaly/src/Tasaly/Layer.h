#pragma once

#include "Tasaly/Core.h"
#include "Tasaly/Events/Event.h"

#include "Tasaly/Core/Timestep.h"

namespace Tasaly {

	class TASALY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

