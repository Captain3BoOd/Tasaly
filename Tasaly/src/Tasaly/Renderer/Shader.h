#pragma once

#include <string>
#include <unordered_map>

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	protected:
		//std::unordered_map<std::string, int> m_Uniforms;
	};

}
