#pragma once

#ifdef TS_PLATFORM_WINDOWS
extern Tasaly::Application* Tasaly::CreateApplication();
	int main(int argc, char** argv)
	{
		Tasaly::Log::Init();
		TS_CORE_WARN("Initialized Log!");
		TS_INFO("Hello! Var = {0}", 5);

		auto app = Tasaly::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Tasaly only support Windows!
#endif // TS_PLATFORM_WINDOWS

