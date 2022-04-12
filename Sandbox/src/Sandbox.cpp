#include "Sandbox.h"

Sandbox::Sandbox(std::string name)
	: Layer(name), cameraController(1280.0f / 720.0f)
{
}

void Sandbox::OnAttach()
{
	texture = Pixie::Texture2D::Create("assets/textures/mario.png");

	Pixie::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	framebuffer = Pixie::Framebuffer::Create(fbSpec);
}

void Sandbox::OnDetach()
{
}

void Sandbox::OnUpdate(Pixie::Timestep ts)
{
	// Update
	cameraController.OnUpdate(ts);

	// Render
	//framebuffer->Bind();
	Pixie::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Pixie::RenderCommand::Clear();

	Pixie::Renderer2D::BeginScene(cameraController.GetCamera());

	Pixie::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Pixie::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Pixie::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.0f, 1.0f }, 180.0f, texture, 10.0f, { 0.0f, 1.0f, 0.0f, 1.0f });

	Pixie::Renderer2D::EndScene();
	//framebuffer->Unbind();
}

void Sandbox::OnImGuiRender()
{
}

void Sandbox::OnEvent(Pixie::Event& e)
{
	cameraController.OnEvent(e);
}