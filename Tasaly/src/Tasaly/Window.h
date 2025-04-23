#pragma once

#include "tspch.h"

#include "Tasaly/Core.h"
#include "Tasaly/Events/Event.h"

namespace Tasaly {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(
			std::string title = "Tasaly Engine",
			unsigned int width = 1200,
			unsigned int height = 700
		): Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based window
	class TASALY_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallBack(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
