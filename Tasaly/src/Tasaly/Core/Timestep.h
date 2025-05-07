#pragma once

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API Timestep
	{
	public:
		Timestep(float time = 0):
			m_Time(time) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}
