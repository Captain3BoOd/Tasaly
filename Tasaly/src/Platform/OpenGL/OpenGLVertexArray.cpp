#include "tspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Tasaly {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Tasaly::ShaderDataType::Float:  return GL_FLOAT;
			case Tasaly::ShaderDataType::Float2: return GL_FLOAT;
			case Tasaly::ShaderDataType::Float3: return GL_FLOAT;
			case Tasaly::ShaderDataType::Float4: return GL_FLOAT;
			case Tasaly::ShaderDataType::Mat3:   return GL_FLOAT;
			case Tasaly::ShaderDataType::Mat4:   return GL_FLOAT;
			case Tasaly::ShaderDataType::Int:    return GL_INT;
			case Tasaly::ShaderDataType::Int2:   return GL_INT;
			case Tasaly::ShaderDataType::Int3:   return GL_INT;
			case Tasaly::ShaderDataType::Int4:   return GL_INT;
			case Tasaly::ShaderDataType::Bool:   return GL_BOOL;
		}

		TS_CORE_ASSERT(false, "UnKnown Shader Data Type");
		return GL_NONE;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		TS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layouts!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			// Vertex Attribute Pointer
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
