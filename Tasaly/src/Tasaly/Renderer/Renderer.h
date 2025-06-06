#pragma once

#include "Tasaly/Core.h"

#include "RenderCommand.h"

#include "OrthographicCamera.h"

#include "Shader.h"

namespace Tasaly {

	class TASALY_API Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};

}
