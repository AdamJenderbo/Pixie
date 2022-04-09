#include "Pixie.h"


class Sandbox : public Pixie::Application
{
public:
	Sandbox()
	{
		Pixie::Console::Log("Sandbox");
	}

protected:
	virtual void Update() override
	{
		Pixie::Console::Log("Updating Sandbox");
	}
};

Pixie::Application* CreateApp()
{
	return new Sandbox();
}