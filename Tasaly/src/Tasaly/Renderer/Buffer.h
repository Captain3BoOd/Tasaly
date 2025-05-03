#pragma once

#include <cstdint>
#include <vector>

#include "Tasaly/Core.h"

namespace Tasaly {

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Tasaly::ShaderDataType::Float:  return 4;
			case Tasaly::ShaderDataType::Float2: return 4 * 2;
			case Tasaly::ShaderDataType::Float3: return 4 * 3;
			case Tasaly::ShaderDataType::Float4: return 4 * 4;
			case Tasaly::ShaderDataType::Mat3:   return 4 * 3 * 3;
			case Tasaly::ShaderDataType::Mat4:   return 4 * 4 * 4;
			case Tasaly::ShaderDataType::Int:    return 4;
			case Tasaly::ShaderDataType::Int2:   return 4 * 2;
			case Tasaly::ShaderDataType::Int3:   return 4 * 3;
			case Tasaly::ShaderDataType::Int4:   return 4 * 4;
			case Tasaly::ShaderDataType::Bool:   return 1;
		}

		TS_CORE_ASSERT(false, "UnKnown Shader Data Type");
		return 0;
	}

	struct TASALY_API BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized = false;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name):
			Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Tasaly::ShaderDataType::Float:  return 1;
				case Tasaly::ShaderDataType::Float2: return 2;
				case Tasaly::ShaderDataType::Float3: return 3;
				case Tasaly::ShaderDataType::Float4: return 4;
				case Tasaly::ShaderDataType::Mat3:   return 3 * 3;
				case Tasaly::ShaderDataType::Mat4:   return 4 * 4;
				case Tasaly::ShaderDataType::Int:    return 1;
				case Tasaly::ShaderDataType::Int2:   return 2;
				case Tasaly::ShaderDataType::Int3:   return 3;
				case Tasaly::ShaderDataType::Int4:   return 4;
				case Tasaly::ShaderDataType::Bool:   return 1;
			}

			TS_CORE_ASSERT(false, "UnKnown Shader Data Type");
			return 0;
		}
	};

	class TASALY_API BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements):
			m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class TASALY_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* data, uint32_t size);
	};

	class TASALY_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* data, uint32_t count);
	};

}
