#pragma once

#include <cstdint>

#include "Tasaly/Core.h"

namespace Tasaly {

	class TASALY_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* data, uint32_t size);
	};

	class TASALY_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* data, uint32_t size);
	};

}
