#include "Pixie.h"
#include "Sandbox.h"

int main()
{
	Pixie::Application* app = new Pixie::Application("Sandbox");
	app->PushLayer(new Sandbox("Sandbox"));
	app->Run();
	delete app;
	return 0;
}