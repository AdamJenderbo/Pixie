#pragma once
#include "Pixie.h"

class Sandbox : public Pixie::Layer
{
public:
	Sandbox(std::string name);

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Pixie::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Pixie::Event& e) override;
private:
	Pixie::OrthographicCameraController cameraController;
	Pixie::Ref<Pixie::Texture2D> texture;
	Pixie::Ref<Pixie::Framebuffer> framebuffer;
};


