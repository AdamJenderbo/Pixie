#include "pxpch.h"
#include "OrthographicCameraController.h"

#include "Pixie/Input.h"
#include "Pixie/KeyCodes.h"

namespace Pixie 
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel), rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::A))
			cameraPosition.x -= cameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::D))
			cameraPosition.x += cameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(Key::W))
			cameraPosition.y += cameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::S))
			cameraPosition.y -= cameraTranslationSpeed * ts;

		if (rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				cameraRotation += cameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				cameraRotation -= cameraRotationSpeed * ts;

			camera.SetRotation(cameraRotation);
		}

		camera.SetPosition(cameraPosition);

		cameraTranslationSpeed = zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		aspectRatio = width / height;
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}

}