#pragma once

#include "Pixie/Renderer/OrthographicCamera.h"
#include "Pixie/Timestep.h"

#include "Pixie/Events/ApplicationEvent.h"
#include "Pixie/Events/MouseEvent.h"

namespace Pixie 
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }

		float GetZoomLevel() const { return zoomLevel; }
		void SetZoomLevel(float level) { zoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float aspectRatio;
		   float zoomLevel = 1.0f;
		   OrthographicCamera camera;

		   bool rotation;

		   glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		   float cameraRotation = 0.0f;
		   float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;
	};

}