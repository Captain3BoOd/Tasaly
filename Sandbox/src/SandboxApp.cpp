#include <functional>
#include <sstream>

#include <Tasaly.h>

class Sandbox: public Tasaly::Application
{
public:
	Sandbox() {}
	~Sandbox() {}

private:

};

Tasaly::Application* Tasaly::CreateApplication()
{
	return new Sandbox();
}

