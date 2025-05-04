#include "tspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tasaly {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}
