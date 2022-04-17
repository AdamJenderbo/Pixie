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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { return colorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return specification; }
	private:
		uint32_t rendererID = 0;
		FramebufferSpecification specification;

		std::vector<FramebufferTextureSpecification> colorAttachmentSpecifications;
		FramebufferTextureSpecification depthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> colorAttachments;
		uint32_t depthAttachment = 0;
	};

}