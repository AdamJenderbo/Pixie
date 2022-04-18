#include "pxpch.h"
#include "Renderer2D.h"


#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Pixie/Renderer/UniformBuffer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace Pixie 
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

		// Editor-only
		int EntityID;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;

		void AddQuad(const glm::mat4 transform, const glm::vec4 color, int textureIndex, float tilingFactor, int entityID)
		{
			AddVertex({ transform * QuadVertexPositions[0], color, {0.0f, 0.0f}, (float) textureIndex, tilingFactor, entityID});
			AddVertex({ transform * QuadVertexPositions[1], color, {1.0f, 0.0f}, (float) textureIndex, tilingFactor, entityID});
			AddVertex({ transform * QuadVertexPositions[2], color, {1.0f, 1.0f}, (float) textureIndex, tilingFactor, entityID});
			AddVertex({ transform * QuadVertexPositions[3], color, {0.0f, 1.0f}, (float) textureIndex, tilingFactor, entityID});

			QuadIndexCount += 6;
		}

		int AddTexture(Ref<Texture2D> texture)
		{
			int textureIndex = TextureSlotIndex;
			TextureSlots[TextureSlotIndex] = texture;
			TextureSlotIndex++;
			return textureIndex;
		}

		int GetIndexOfTexture(Ref<Texture2D> texture)
		{
			for (uint32_t i = 1; i < TextureSlotIndex; i++)
			{
				if (*TextureSlots[i].get() == *texture.get())
					return i;
			}
			return 0;
		}

	private:
		void AddVertex(QuadVertex vertex)
		{
			QuadVertexBufferPtr->Position = vertex.Position;
			QuadVertexBufferPtr->Color = vertex.Color;
			QuadVertexBufferPtr->TexCoord = vertex.TexCoord;
			QuadVertexBufferPtr->TexIndex = vertex.TexIndex;
			QuadVertexBufferPtr->TilingFactor = vertex.TilingFactor;
			QuadVertexBufferPtr->EntityID = vertex.EntityID;
			QuadVertexBufferPtr++;
		}
	};

	static Renderer2DData data;

	void Renderer2D::Init()
	{
		data.QuadVertexArray = VertexArray::Create();

		data.QuadVertexBuffer = VertexBuffer::Create(data.MaxVertices * sizeof(QuadVertex));
		data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"     },
			{ ShaderDataType::Float4, "a_Color"        },
			{ ShaderDataType::Float2, "a_TexCoord"     },
			{ ShaderDataType::Float,  "a_TexIndex"     },
			{ ShaderDataType::Float,  "a_TilingFactor" },
			{ ShaderDataType::Int,    "a_EntityID"     }
		});

		data.QuadVertexArray->AddVertexBuffer(data.QuadVertexBuffer);

		data.QuadVertexBufferBase = new QuadVertex[data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, data.MaxIndices);
		data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[data.MaxTextureSlots];
		for (uint32_t i = 0; i < data.MaxTextureSlots; i++)
			samplers[i] = i;
		data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);

		data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");

		data.TextureSlots[0] = data.WhiteTexture;

		data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		data.CameraUniformBuffer->SetData(&data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		StartBatch();
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		data.CameraUniformBuffer->SetData(&data.CameraBuffer, sizeof(Renderer2DData::CameraData));

		StartBatch();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data.TextureShader->Bind();
		data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)data.QuadVertexBufferPtr - (uint8_t*)data.QuadVertexBufferBase;
		data.QuadVertexBuffer->SetData(data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::StartBatch()
	{
		data.QuadIndexCount = 0;
		data.QuadVertexBufferPtr = data.QuadVertexBufferBase;

		data.TextureSlotIndex = 1;
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < data.TextureSlotIndex; i++)
			data.TextureSlots[i]->Bind(i);

		data.TextureShader->Bind();
		RenderCommand::DrawIndexed(data.QuadVertexArray, data.QuadIndexCount);
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, int entityID)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, entityID);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color, entityID);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::mat4 transform, const glm::vec4& color, int entityID)
	{
		if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		const int textureIndex = 0;
		const float tilingFactor = 1.0f;

		data.AddQuad(transform, color, textureIndex, tilingFactor, entityID);
	}

	void Renderer2D::DrawQuad(const glm::mat4 transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		int textureIndex = data.GetIndexOfTexture(texture);

		if (textureIndex == 0)
			textureIndex = data.AddTexture(texture);

		data.AddQuad(transform, color, textureIndex, tilingFactor, entityID);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, int entityID)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color, entityID);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, int entityID)
	{
		if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		const int textureIndex = 0;
		const float tilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		data.AddQuad(transform, color, textureIndex, tilingFactor, entityID);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor, entityID);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor, int entityID)
	{
		if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		int textureIndex = data.GetIndexOfTexture(texture);

		if (textureIndex == 0)
			textureIndex = data.AddTexture(texture);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		data.AddQuad(transform, color, textureIndex, tilingFactor, entityID);
	}
	void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteRendererComponent& spriteRenderer, int entityID)
	{
		DrawQuad(transform, spriteRenderer.Color, entityID);
	}
}