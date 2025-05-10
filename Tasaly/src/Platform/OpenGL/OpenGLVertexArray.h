#pragma once

#include "Tasaly/Renderer/VertexArray.h"

namespace Tasaly {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };
	private:
		uint32_t m_RendererID = 0;
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
	};

}
