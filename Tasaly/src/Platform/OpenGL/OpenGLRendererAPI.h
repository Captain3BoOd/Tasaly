#pragma once

#include "Tasaly/Renderer/RendererAPI.h"

namespace Tasaly {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}
