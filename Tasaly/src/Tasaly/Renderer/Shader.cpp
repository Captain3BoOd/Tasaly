#include "tspch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer.h"

namespace Tasaly {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case Tasaly::RendererAPI::API::None:   TS_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
			case Tasaly::RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
			//case Tasaly::RendererAPI::API::Vulkan:
			//case Tasaly::RendererAPI::API::Direct3D:
		}

		TS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
