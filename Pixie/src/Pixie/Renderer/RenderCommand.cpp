#include "pxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Pixie 
{
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}