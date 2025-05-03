#pragma once

#include <string>

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}
