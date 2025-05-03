#include "tspch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace Tasaly {

	VertexBuffer* VertexBuffer::Create(float* data, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case Tasaly::RendererAPI::None:   TS_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case Tasaly::RendererAPI::OpenGL: return new OpenGLVertexBuffer(data, size);
			//case Tasaly::RendererAPI::Vulkan:
			//case Tasaly::RendererAPI::Direct3D:
		}

		TS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case Tasaly::RendererAPI::None:   TS_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case Tasaly::RendererAPI::OpenGL: return new OpenGLIndexBuffer(data, count);
			//case Tasaly::RendererAPI::Vulkan:
			//case Tasaly::RendererAPI::Direct3D:
		}

		TS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
