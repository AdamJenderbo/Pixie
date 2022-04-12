#pragma once

#include "Pixie/Renderer/Framebuffer.h"

namespace Pixie 
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;


		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return specification; }
	private:
		uint32_t rendererID = 0;
		uint32_t colorAttachment = 0, depthAttachment = 0;
		FramebufferSpecification specification;
	};

}