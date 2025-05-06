#pragma once

#include <string>
#include <unordered_map>

#include "Tasaly/Core.h"

#include <glm/glm.hpp>

namespace Tasaly {

	class TASALY_API Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	protected:
		//std::unordered_map<std::string, int> m_Uniforms;
	};

}
