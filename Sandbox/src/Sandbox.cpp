#include "Pixie.h"


class Sandbox : public Pixie::Application
{
public:
	Sandbox()
	{
	}

protected:
	virtual void OnUpdate() override
	{
		if (Pixie::Input::IsKeyPressed(Pixie::KeyCode::Left))
		{
			Pixie::Console::Log("Pressed left!");
		}
	}
};

Pixie::Application* CreateApp()
{
	return new Sandbox();
}