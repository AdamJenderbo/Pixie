#include "pxpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Pixie 
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Pixie::ShaderDataType::Float:    return GL_FLOAT;
		case Pixie::ShaderDataType::Float2:   return GL_FLOAT;
		case Pixie::ShaderDataType::Float3:   return GL_FLOAT;
		case Pixie::ShaderDataType::Float4:   return GL_FLOAT;
		case Pixie::ShaderDataType::Mat3:     return GL_FLOAT;
		case Pixie::ShaderDataType::Mat4:     return GL_FLOAT;
		case Pixie::ShaderDataType::Int:      return GL_INT;
		case Pixie::ShaderDataType::Int2:     return GL_INT;
		case Pixie::ShaderDataType::Int3:     return GL_INT;
		case Pixie::ShaderDataType::Int4:     return GL_INT;
		case Pixie::ShaderDataType::Bool:     return GL_BOOL;
		}

		Console::LogError("Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		if(!vertexBuffer->GetLayout().GetElements().size()) 
			Console::LogError("Vertex Buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID);
		indexBuffer->Bind();

		this->indexBuffer = indexBuffer;
	}

}