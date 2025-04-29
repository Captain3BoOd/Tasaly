#pragma once

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}
