#include "tspch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Renderer.h"

namespace Tasaly {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case Tasaly::RendererAPI::API::None:   TS_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case Tasaly::RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
			//case Tasaly::RendererAPI::API::Vulkan:
			//case Tasaly::RendererAPI::API::Direct3D:
		}

		TS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
