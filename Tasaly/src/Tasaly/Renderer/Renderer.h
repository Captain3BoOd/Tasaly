#pragma once

#include "Tasaly/Core.h"

namespace Tasaly {

	enum class RendererAPI
	{
		None = 0,
		OpenGL,
		Vulkan,
		Direct3D
	};

	class TASALY_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};

}
