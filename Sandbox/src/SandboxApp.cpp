#include <functional>
#include <sstream>

#include <Tasaly.h>

#include "Platform/OpenGL/OpenGLShader.h" 

#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public Tasaly::Layer
{
public:
	ExampleLayer():
		Layer("Example"),
		m_SquarePosition(0.0f),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		// Vertex Array
		m_VertexArray.reset(Tasaly::VertexArray::Create());

		// Vertex Buffer
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		Tasaly::Ref<Tasaly::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Tasaly::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ Tasaly::ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer); // must be after add a layout

		// Index Buffer
		unsigned int indices[3] = {
			0, 1, 2
		};

		Tasaly::Ref<Tasaly::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tasaly::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square Draw Test
		m_SquareVA.reset(Tasaly::VertexArray::Create());

		// Vertex buffer for square draw test
		float squareVertices[3 * 4 + 2 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Tasaly::Ref<Tasaly::VertexBuffer> squareVB;
		squareVB.reset(Tasaly::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Tasaly::ShaderDataType::Float3, "a_Position" },
			{ Tasaly::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB); // must be after add a layout

		// Index buffer for square draw test
		unsigned int squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		Tasaly::Ref<Tasaly::IndexBuffer> squareIB;
		squareIB.reset(Tasaly::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Square Draw Test Shaders
		std::string SquarevertexShader = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";
		std::string SquarefragmentShader = R"(
			#version 450 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";
		m_SquareShader.reset(Tasaly::Shader::Create(SquarevertexShader, SquarefragmentShader));

		// Shaders
		std::string vertexShader = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";
		std::string fragmentShader = R"(
			#version 450 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}

		)";
		m_Shader.reset(Tasaly::Shader::Create(vertexShader, fragmentShader));

		// Texture Shader
		std::string textureVertexShader = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";
		std::string textureFragmentShader = R"(
			#version 450 core

			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}

		)";

		m_TextureShader.reset(Tasaly::Shader::Create(textureVertexShader, textureFragmentShader));
		m_Texture = Tasaly::Texture2D::Create("assets/texture.png");
		m_ChickenTexture = Tasaly::Texture2D::Create("assets/texture2.png");

		std::dynamic_pointer_cast<Tasaly::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Tasaly::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Tasaly::Timestep ts) override
	{
		TS_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		Tasaly::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Tasaly::RenderCommand::Clear();

		glm::vec3 newPos = m_Camera.GetPosition();
		float newRotation = m_Camera.GetRotation();

		if (m_InProccess)
		{
			glm::vec3 defaultPos = glm::vec3(0.0f);
			float defaultRotation = 0.0f;

			if (newRotation == defaultRotation && newPos == defaultPos)
			{
				m_InProccess = false;
			}
			else
			{
				if (newRotation > 0.0f) newRotation -= m_CameraRotationSpeed * 0.5f * ts;
				else if (newRotation < 0.0f) newRotation += m_CameraRotationSpeed * 0.5f * ts;

				if (newPos.x > 0.0f) newPos.x -= m_CameraMoveSpeed * 0.5f * ts;
				else if (newPos.x < 0.0f) newPos.x += m_CameraMoveSpeed * 0.5f * ts;

				if (newPos.y > 0.0f) newPos.y -= m_CameraMoveSpeed * 0.5f * ts;
				else if (newPos.y < 0.0f) newPos.y += m_CameraMoveSpeed * 0.5f * ts;
			}
		}

		if (Tasaly::Input::IsKeyPressed(TS_KEY_UP))
			newPos.y -= m_CameraMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_DOWN))
			newPos.y += m_CameraMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_RIGHT))
			newPos.x -= m_CameraMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_LEFT))
			newPos.x += m_CameraMoveSpeed * ts;

		if (Tasaly::Input::IsKeyPressed(TS_KEY_I))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_K))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_L))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_J))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (Tasaly::Input::IsKeyPressed(TS_KEY_E))
			newRotation += m_CameraRotationSpeed * ts;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_Q))
			newRotation -= m_CameraRotationSpeed * ts;

		if (Tasaly::Input::IsKeyPressed(TS_KEY_R))
			m_InProccess = true;
		if (Tasaly::Input::IsKeyPressed(TS_KEY_T))
			m_InProccess = false;

		m_Camera.SetPosition(newPos);
		m_Camera.SetRotation(newRotation);

		// Begin Scene
		Tasaly::Renderer::BeginScene(m_Camera);
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			glm::vec4 redColor(0.8f, 0.3f, 0.2f, 1.0f);
			glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
			
			std::dynamic_pointer_cast<Tasaly::OpenGLShader>(m_SquareShader)->Bind();
			std::dynamic_pointer_cast<Tasaly::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

			for (size_t x = 0; x < 5; x++)
			{
				for (size_t y = x; y < 5; y++)
				{
					glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
					Tasaly::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
				}
			}

			m_Texture->Bind();
			Tasaly::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			m_ChickenTexture->Bind();
			Tasaly::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			// Draw
			//Tasaly::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Tasaly::Renderer::EndScene();
		// End Scene
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		{
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		}
		ImGui::End();
	}

	void OnEvent(Tasaly::Event& event) override
	{

	}
private:
	Tasaly::Ref<Tasaly::Shader> m_Shader;
	Tasaly::Ref<Tasaly::VertexArray> m_VertexArray;

	Tasaly::Ref<Tasaly::Shader> m_SquareShader, m_TextureShader;
	Tasaly::Ref<Tasaly::VertexArray> m_SquareVA;

	Tasaly::Ref<Tasaly::Texture2D> m_Texture, m_ChickenTexture;

	Tasaly::OrthographicCamera m_Camera;
	float m_CameraMoveSpeed = 3.0f;
	float m_CameraRotationSpeed = 100.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 2.5f;

	bool m_InProccess = false;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox: public Tasaly::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

private:

};

Tasaly::Application* Tasaly::CreateApplication()
{
	return new Sandbox();
}

