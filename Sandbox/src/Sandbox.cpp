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
	}
};

Pixie::Application* CreateApp()
{
	return new Sandbox();
}