#pragma once

#include "RendererAPI.h"

namespace Pixie 
{

	class RenderCommand
	{
	public:

		inline static void Init()
		{
			rendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			rendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count = 0)
		{
			rendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static RendererAPI* rendererAPI;
	};

}