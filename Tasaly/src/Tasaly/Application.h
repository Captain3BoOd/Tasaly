#pragma once

#include "Core.h"

namespace Tasaly {

	class TASALY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}