#include "Pixie.h"
#include "Editor.h"

int main(int argc, char** argv)
{
	Pixie::Application* app = new Pixie::Application("Pixie", { argc, argv });
	app->PushLayer(new Pixie::Editor());
	app->Run();
	delete app;
	return 0;
}