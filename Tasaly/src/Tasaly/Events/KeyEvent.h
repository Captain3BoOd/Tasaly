#pragma once

#include "Tasaly/Core.h"
#include "Event.h"

namespace Tasaly {

	class TASALY_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int KeyCode):
			m_KeyCode(KeyCode) {}

		int m_KeyCode;
	};

	class TASALY_API KeyPressedEvent: public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCode):
			KeyEvent(KeyCode), m_RepeatCount(RepeatCode) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ") repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class TASALY_API KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode):
			KeyEvent(KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
