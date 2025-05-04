#include "tspch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Renderer.h"

namespace Tasaly {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case Tasaly::RendererAPI::API::None:   TS_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case Tasaly::RendererAPI::API::OpenGL: return new OpenGLVertexArray();
			//case Tasaly::RendererAPI::API::Vulkan:
			//case Tasaly::RendererAPI::API::Direct3D:
		}

		TS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
