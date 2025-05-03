#pragma once

#include <string>

#include "Tasaly/Renderer/Shader.h"

namespace Tasaly {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		uint32_t m_RendererID = 0;
	};

}
