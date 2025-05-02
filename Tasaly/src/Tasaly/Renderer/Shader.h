#pragma once

#include <string>

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		void Bind() const;
		void UnBind() const;
	private:
		uint32_t m_RendererID = 0;
	};

}
