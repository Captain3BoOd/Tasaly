#pragma once

#ifdef TS_PLATFORM_WINDOWS
extern Tasaly::Application* Tasaly::CreateApplication();
	int main(int argc, char** argv)
	{
		auto app = Tasaly::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Tasaly only support Windows!
#endif // TS_PLATFORM_WINDOWS

