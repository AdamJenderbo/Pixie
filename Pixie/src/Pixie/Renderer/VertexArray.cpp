#include "pxpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Pixie 
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: Console::LogError("RendererAPI::None is currently not supported!"); return nullptr;;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		Console::LogError("Unknown RendererAPI!");
		return nullptr;
	}

}