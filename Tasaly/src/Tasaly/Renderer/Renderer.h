#pragma once

#include "Tasaly/Core.h"

#include "RenderCommand.h"

#include "OrthographicCamera.h"

#include "Shader.h"

namespace Tasaly {

	class TASALY_API Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};

}
