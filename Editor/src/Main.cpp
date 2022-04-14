#include "Pixie.h"
#include "Editor.h"

int main()
{
	Pixie::Application* app = new Pixie::Application("Editor");
	app->PushLayer(new Pixie::Editor());
	app->Run();
	delete app;
	return 0;
}