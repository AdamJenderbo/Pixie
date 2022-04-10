#pragma once
#include "Pixie.h"

class Sandbox : public Pixie::Layer
{
public:
	Sandbox(std::string name);

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Pixie::Event& e) override;
};


