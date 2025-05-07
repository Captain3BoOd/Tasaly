#include <functional>
#include <sstream>

#include <Tasaly.h>

#include "imgui/imgui.h"

class ExampleLayer : public Tasaly::Layer
{
public:
	ExampleLayer():
		Layer("Example"),
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

		std::shared_ptr<Tasaly::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Tasaly::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{ Tasaly::ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer); // must be after add a layout

		// Index Buffer
		unsigned int indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<Tasaly::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tasaly::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square Draw Test
		m_SquareVA.reset(Tasaly::VertexArray::Create());

		// Vertex buffer for square draw test
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<Tasaly::VertexBuffer> squareVB;
		squareVB.reset(Tasaly::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Tasaly::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB); // must be after add a layout

		// Index buffer for square draw test
		unsigned int squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<Tasaly::IndexBuffer> squareIB;
		squareIB.reset(Tasaly::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Square Draw Test Shaders
		std::string SquarevertexShader = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";
		std::string SquarefragmentShader = R"(
			#version 450 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.25 + 0.25, 1.0);
			}

		)";
		m_SquareShader.reset(Tasaly::Shader::Create(SquarevertexShader, SquarefragmentShader));

		// Shaders
		std::string vertexShader = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
	}

	void OnUpdate() override
	{
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
				if (newRotation > 0.0f) newRotation -= m_CameraRotationSpeed;
				else if (newRotation < 0.0f) newRotation += m_CameraRotationSpeed;

				if (newPos.x > 0.0f) newPos.x -= m_CameraMoveSpeed;
				else if (newPos.x < 0.0f) newPos.x += m_CameraMoveSpeed;

				if (newPos.y > 0.0f) newPos.y -= m_CameraMoveSpeed;
				else if (newPos.y < 0.0f) newPos.y += m_CameraMoveSpeed;
			}
		}
		else
		{
			if (Tasaly::Input::IsKeyPressed(TS_KEY_UP))
				newPos.y -= m_CameraMoveSpeed;
			if (Tasaly::Input::IsKeyPressed(TS_KEY_DOWN))
				newPos.y += m_CameraMoveSpeed;
			if (Tasaly::Input::IsKeyPressed(TS_KEY_RIGHT))
				newPos.x -= m_CameraMoveSpeed;
			if (Tasaly::Input::IsKeyPressed(TS_KEY_LEFT))
				newPos.x += m_CameraMoveSpeed;

			if (Tasaly::Input::IsKeyPressed(TS_KEY_A))
				newRotation += m_CameraRotationSpeed;
			if (Tasaly::Input::IsKeyPressed(TS_KEY_D))
				newRotation -= m_CameraRotationSpeed;

			if (Tasaly::Input::IsKeyPressed(TS_KEY_R))
			{
				m_InProccess = true;
			}
		}

		m_Camera.SetPosition(newPos);
		m_Camera.SetRotation(newRotation);

		// Begin Scene
		Tasaly::Renderer::BeginScene(m_Camera);
		{
			// Square Draw Test
			Tasaly::Renderer::Submit(m_SquareShader, m_SquareVA);

			// Draw
			Tasaly::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Tasaly::Renderer::EndScene();
		// End Scene
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Tasaly::Event& event) override
	{

	}
private:
	std::shared_ptr<Tasaly::Shader> m_Shader;
	std::shared_ptr<Tasaly::VertexArray> m_VertexArray;

	std::shared_ptr<Tasaly::Shader> m_SquareShader;
	std::shared_ptr<Tasaly::VertexArray> m_SquareVA;

	Tasaly::OrthographicCamera m_Camera;
	float m_CameraMoveSpeed = 0.03f;
	float m_CameraRotationSpeed = 2.0f;

	bool m_InProccess = false;
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

