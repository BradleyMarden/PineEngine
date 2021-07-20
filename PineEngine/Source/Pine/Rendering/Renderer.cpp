#include "Renderer.h"
namespace Pine {
	 static const size_t m_MaxQuadCount = 1000;					//per flush
	 static const size_t m_MaxVertexCount = m_MaxQuadCount * 4;	//each quad has 4 vertex
	 static const size_t m_MaxIndexCount = m_MaxQuadCount * 6;	//each quad has 6 index
	 static const size_t m_MaxTextureCount = 32;

	SDL_Renderer**	Renderer::renderer;
	bool Renderer::limitFPS = false;
	bool Renderer::hasRun = false;
	bool Renderer::m_IconSet = false;

	struct Vertex
	{
		glm::vec3 s_Position;
		glm::vec4 s_Color;
		glm::vec2 s_TextureCoords;
		float s_TextureIndex;

	};

	struct RendererData
	{
		GLuint s_VertexArray;
		GLuint s_VertexBuffer;
		GLuint s_IndexBuffer;
		GLuint s_WhiteTexture = 0;

		uint32_t s_WHiteTextureSlot = 0;
		uint32_t s_IndexCount = 0;

		Vertex* buffer = nullptr;//holds all vertices
		Vertex* bufferPtr = nullptr;//reference to a single vertex in above

		std::array<uint32_t, m_MaxTextureCount> s_TextureSlots;
		uint32_t s_TextureSlotIndex = 1;

		int renderCalls;
		int indexCount;
		int quadCount;
	};
	static RendererData m_RendererData;


	void Renderer::GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}
	void Renderer::GLCheckError()
	{
		//PINE_ENGINE_INFO("Checking gl");
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "GL ERROR: " << err << std::endl;
		}
	}

	static unsigned int shader;

	void Renderer::InitRendering()
	{

		renderer = &Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Renderer;
		m_RendererData.buffer = new Vertex[m_MaxVertexCount];
		Window::SetWindowToRendeer(Window::GetMainWindow()->s_WindowName);
		if (renderer == nullptr)
		{
			PINE_ENGINE_WARN("Rendering NOT loaded");
		}
		PINE_ENGINE_WARN("Rendering loaded");
		//load shader
		SourceShader localShaders = Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
		shader = Shader::CreateShader(localShaders.VertexSource, localShaders.FragmentSource);
		glUseProgram(shader);


		//TEXTURE
			//load texture
		CreateWhiteTexture();//must be called first as it sets all remaining tex slots to zero for safety;
		m_RendererData.s_TextureSlots[1] = LoadTexture("Assets/PineEngineText.png");
		m_RendererData.s_TextureSlots[2] = LoadTexture("Assets/PineEngine.png");

		//set texture
		int location = glGetUniformLocation(shader, "u_tex");
		int samplers[3] = { 0,1,2 };
		glUniform1iv(location, 3, samplers);
		//VERTEX LAYOUT  

		glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));//controls positon of object on screen
		glm::mat4 mvp = projection * view * model;

		//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		int location2 = glGetUniformLocation(shader, "u_Proj");
		glUniformMatrix4fv(location2, 1, GL_FALSE, &mvp[0][0]);


		//set and bind vertex array
		glCreateVertexArrays(1, &m_RendererData.s_VertexArray);
		GLCheckError();

		glBindVertexArray(m_RendererData.s_VertexArray);
		GLCheckError();

		//set and bind buffers
		glCreateBuffers(1, &m_RendererData.s_VertexBuffer);
		GLCheckError();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererData.s_VertexBuffer);
		GLCheckError();

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_MaxVertexCount, nullptr , GL_DYNAMIC_DRAW);
		GLCheckError();

		//SHADER PROPERTIES
		//POSITION
		//glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 0);
		glEnableVertexAttribArray(0);
		GLCheckError();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_Position));
		GLCheckError();
		//COLOR
		//glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 1);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_Color));
		GLCheckError();
		//TEX COORD
		glEnableVertexAttribArray(2);
		GLCheckError();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_TextureCoords));
		GLCheckError();
		//TEX INDEX
		glEnableVertexAttribArray(3);
		GLCheckError();
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_TextureIndex));
		GLCheckError();

		//set Indices
		uint32_t indices[m_MaxIndexCount];
		uint32_t offset = 0;

		for (int i = 0; i < m_MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;

		}

		glCreateBuffers(1, &m_RendererData.s_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererData.s_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	/*//SHADER///////////////////////////////////////////////////////////////////////////////////////////////////
		//load shader
		SourceShader localShaders = Pine::Shader::LoadShader("Assets/Shaders/default.PineShader");
		shader  = Shader::CreateShader(localShaders.VertexSource, localShaders.FragmentSource);
		 glUseProgram(shader);


	//TEXTURE
		//load texture
		m_RendererData.s_TextureSlots[0] = LoadTexture("Assets/PineEngineText.png");
		m_RendererData.s_TextureSlots[1] = LoadTexture("Assets/PineEngine.png");
		
		//set texture
		int location = glGetUniformLocation(shader, "u_tex");
		int samplers[2] = { 0,1 };
		glUniform1iv(location, 2, samplers);
	//VERTEX LAYOUT  

		glm::mat4 projection = glm::ortho(0.0f, Window::GetMainWindow()->s_WindowSize.x, 0.0f, Window::GetMainWindow()->s_WindowSize.y, -1.0f, 1.0f);//converts screen space to values between -1:1
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));//can be used to imitate move camera(works by shifting all onjects in scene)
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));//controls positon of object on screen
		glm::mat4 mvp = projection * view * model;

		//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		int location2 = glGetUniformLocation(shader, "u_Proj");
		glUniformMatrix4fv(location2, 1, GL_FALSE, &mvp[0][0]);


		float VertexArray[] =
		{
			100.f, 100.f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f,0.0f,//0
			200.f, 100.f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f,0.0f,//1
			200.f,  200.f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f,0.0f,//2
			100.f,  200.f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f,0.0f,//

			300.f, 300.f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 1.0f,1.0f,
			400.f, 300.f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 1.0f,1.0f,
			401.f,  400.f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 0.0f,1.0f,
			300.f,  400.f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 0.0f,1.0f


		};


		glCreateVertexArrays(1, &m_RendererData.s_VertexArray);
		GLCheckError();


		glBindVertexArray(m_RendererData.s_VertexArray);
		GLCheckError();
		



		glCreateBuffers(1, &m_RendererData.s_VertexBuffer);
		GLCheckError();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererData.s_VertexBuffer);
		GLCheckError();

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexArray), VertexArray, GL_STATIC_DRAW);
		GLCheckError();

	//SHADER PROPERTIES


		//POSITION
		//glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 0);
		glEnableVertexAttribArray(0);
		GLCheckError();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), 0);
		GLCheckError();
		//COLOR
		//glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 1);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)12);
		GLCheckError();
		//TEX COORD
		glEnableVertexAttribArray(2);
		GLCheckError();
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)28);
		GLCheckError();
		//TEX INDEX
		glEnableVertexAttribArray(3);
		GLCheckError();
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)36);
		GLCheckError();

		//INDICES
		unsigned int indices[]
		{
			0,1,2,2,3,0,
			4,5,6,6,7,4

		};

		glCreateBuffers(1, &m_RendererData.s_IndexBuffer);
		GLCheckError();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererData.s_IndexBuffer);
		GLCheckError();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		GLCheckError();

		*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//SDL_SetRenderDrawColor(*renderer, 21, 27, 31, 255);

	////////////////////////////////////////

		/*m_RendererData.buffer = new Vertex[m_MaxQuadCount];

		glCreateVertexArrays(1, &m_RendererData.s_VertexArray);
		glBindVertexArray(m_RendererData.s_VertexArray);

		glCreateBuffers(1, &m_RendererData.s_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererData.s_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 0);
		glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_Position));

		glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_Color));

		glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_TextureCoords));

		glEnableVertexArrayAttrib(m_RendererData.s_VertexBuffer, 3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, s_TextureIndex));

		uint32_t indices[m_MaxIndexCount];
		uint32_t offset = 0;

		for (int i = 0; i < m_MaxIndexCount; i += 6) 
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		
		}
		glCreateBuffers(1, & m_RendererData.s_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererData.s_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		
		glCreateTextures(GL_TEXTURE_2D,1,&m_RendererData.s_WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, m_RendererData.s_WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		GLuint color = 0xffffffff;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE, &color);
		m_RendererData.s_TextureSlots[0] = m_RendererData.s_WhiteTexture;
		for (size_t i = 1; i < m_MaxTextureCount; i++)
		{
			m_RendererData.s_TextureSlots[i] = 0;
		}
		*/




		//Setup IMGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window, Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Context);
		ImGui_ImplOpenGL3_Init("#version 450");
		hasRun = true;
	}
	void Renderer::Shutdown() 
	{
		glDeleteVertexArrays(1, & m_RendererData.s_VertexArray);
		glDeleteBuffers(1, & m_RendererData.s_VertexBuffer);
		glDeleteBuffers(1, &m_RendererData.s_IndexBuffer);
		glDeleteTextures(1, &m_RendererData.s_WhiteTexture);
		delete[] m_RendererData.buffer;
	}

	void Renderer::BeginBatch() 
	{
		/*

		//CLEAR SCREEN
		glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
		GLCheckError();
		//LOAD SHADER AND TEXTURES
		glUseProgram(shader);
		glBindTextureUnit(0, m_RendererData.s_TextureSlots[0]);
		glBindTextureUnit(1, m_RendererData.s_TextureSlots[1]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCheckError();

		//DRAW
		//glBindVertexArray(m_RendererData.s_VertexArray);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
		GLCheckError();
		RenderUI();
		if (Window::GetMainWindow() != nullptr)
		{
			SDL_GL_SwapWindow(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window);
			GLCheckError();
			glUseProgram(0);

		}

		*/
		//set the bufferptr to the first vertex
		m_RendererData.bufferPtr = m_RendererData.buffer;
		
	}
	void Renderer::EndBatch() 
	{
		GLsizeiptr size = (uint8_t*)m_RendererData.bufferPtr - (uint8_t*)m_RendererData.buffer;
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererData.s_VertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0,size,m_RendererData.buffer);
	
	}

	void Renderer::ResetStats()
	{
		m_RendererData.quadCount = 0;
		m_RendererData.indexCount = 0;
		m_RendererData.renderCalls = 0;
	
	}

	void Renderer::Flush() 
	{
		/*for (uint32_t i = 0; i < m_RendererData.s_TextureSlotIndex; i++)
		{
			glBindTextureUnit(i, m_RendererData.s_TextureSlots[i]);
		}*/

		glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
		GLCheckError();
		//LOAD SHADER AND TEXTURES
		glUseProgram(shader);
		glBindTextureUnit(0, m_RendererData.s_TextureSlots[0]);
		glBindTextureUnit(1, m_RendererData.s_TextureSlots[1]);
		glBindTextureUnit(2, m_RendererData.s_TextureSlots[2]);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCheckError();

		//DRAW
		glBindVertexArray(m_RendererData.s_VertexArray);
		glDrawElements(GL_TRIANGLES, m_RendererData.s_IndexCount, GL_UNSIGNED_INT, nullptr);
		GLCheckError();
		RenderUI();
		if (Window::GetMainWindow() != nullptr)
		{
			SDL_GL_SwapWindow(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window);
			GLCheckError();
			glUseProgram(0);

		}
		m_RendererData.renderCalls++;
		m_RendererData.s_IndexCount = 0;
		//m_RendererData.s_TextureSlotIndex = 1;

		//was working/////////////////
		/*
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		//SDL_RenderClear(*renderer);
		//SDL_RenderPresent(*renderer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		RenderUI();

		//gives error
		if (Window::GetMainWindow() != nullptr)
		{
			SDL_GL_SwapWindow(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window);

		}
		*///////////////////////

		//glBindVertexArray(m_RendererData.s_VertexArray);
		//glDrawElements(GL_TRIANGLES, m_RendererData.s_IndexCount, GL_UNSIGNED_INT, nullptr);
		//m_RendererData.renderCalls++;
		//m_RendererData.s_IndexCount = 0;
		//m_RendererData.s_TextureSlotIndex = 1;
		//RenderUI();


	}
	void Renderer::RenderUI()
	{

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window);
		//IMGUI CREATE FRAME
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(Window::GetMainWindow()->s_WindowSize.x <= 1000 ? ImVec2(Window::GetMainWindow()->s_WindowSize.x / 3, Window::GetMainWindow()->s_WindowSize.y/ 3) : ImVec2(400, 150), ImGuiCond_Always);



		static float f = 0.0f;
		//IMGUI START
		ImGui::Begin("PineEngine");
		ImGui::Text("Window Width: %f", Window::GetMainWindow()->s_WindowSize.x);
		ImGui::Text("Window Height: %f", Window::GetMainWindow()->s_WindowSize.y);
		ImGui::Checkbox("Limit FPS to 60", &limitFPS);
		//if (ImGui::Checkbox("Limit FPS to 60", &limitFPS))
			//limitFPS = !limitFPS;
		PVector2f mousePos = Input::GetMousePosition();
		ImGui::Text("Mouse X pos: %f", mousePos.X);
		ImGui::Text("Mouse Y pos: %f", mousePos.Y);
		ImGui::Text("Render Calls %i", m_RendererData.renderCalls);
		ImGui::Text("Quad Count %i", m_RendererData.quadCount);
		ImGui::Text("Index Count %i", m_RendererData.indexCount);

		if (ImGui::Button("Open New Window"))
			Window::CreateNewWindow("ImGUI");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		//IMGUI END

		//IMGUI RENDER
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Renderer::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color) 
	{
		PINE_ENGINE_WARN(m_RendererData.quadCount);
		if (m_RendererData.s_IndexCount >= m_MaxIndexCount)
		{
			PINE_ENGINE_WARN("START AGAIN");

			EndBatch();
			Flush();
			BeginBatch();
		}
		float textureIndex = 0.0f;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x, p_Pos.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = p_Color;
		m_RendererData.bufferPtr->s_TextureCoords = { 0.0f, 0.0f };
		m_RendererData.bufferPtr->s_TextureIndex = textureIndex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x + p_Size.x, p_Pos.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = p_Color;
		m_RendererData.bufferPtr->s_TextureCoords = { 1.0f, 0.0f };
		m_RendererData.bufferPtr->s_TextureIndex = textureIndex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x + p_Size.x, p_Pos.y + p_Size.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = p_Color;
		m_RendererData.bufferPtr->s_TextureCoords = { 1.0f, 1.0f };
		m_RendererData.bufferPtr->s_TextureIndex = textureIndex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x, p_Pos.y + p_Size.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = p_Color;
		m_RendererData.bufferPtr->s_TextureCoords = { 0.0f, 1.0f };
		m_RendererData.bufferPtr->s_TextureIndex = textureIndex;
		m_RendererData.bufferPtr++;


		m_RendererData.s_IndexCount += 6;

		m_RendererData.quadCount++;
		
	
	}
	void Renderer::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint tex) 
	{
		PINE_ENGINE_WARN(m_RendererData.quadCount);
		if (m_RendererData.s_IndexCount >= m_MaxIndexCount)
		{
			PINE_ENGINE_WARN("START AGAIN");

			EndBatch();
			Flush();
			BeginBatch();
		}
		//float textureIndex = 0.0f;
		glm::vec4 col = { 1.0f,1.0f,1.0f,1.0f };

		m_RendererData.bufferPtr->s_Position = { p_Pos.x, p_Pos.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = col;
		m_RendererData.bufferPtr->s_TextureCoords = { 0.0f, 0.0f };
		m_RendererData.bufferPtr->s_TextureIndex = tex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x + p_Size.x, p_Pos.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = col;
		m_RendererData.bufferPtr->s_TextureCoords = { 1.0f, 0.0f };
		m_RendererData.bufferPtr->s_TextureIndex = tex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x + p_Size.x, p_Pos.y + p_Size.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = col;
		m_RendererData.bufferPtr->s_TextureCoords = { 1.0f, 1.0f };
		m_RendererData.bufferPtr->s_TextureIndex = tex;
		m_RendererData.bufferPtr++;

		m_RendererData.bufferPtr->s_Position = { p_Pos.x, p_Pos.y + p_Size.y, 0.0f };
		m_RendererData.bufferPtr->s_Color = col;
		m_RendererData.bufferPtr->s_TextureCoords = { 0.0f, 1.0f };
		m_RendererData.bufferPtr->s_TextureIndex = tex;
		m_RendererData.bufferPtr++;


		m_RendererData.s_IndexCount += 6;

		m_RendererData.quadCount++;

	
	}

	void Renderer::CreateQuad(const char* p_Name, int p_Width, int p_Height, GLuint p_Shader)
	{
	
	
	}
	void Renderer::SetWindowIcon(const char* path)
	{
		SDL_Surface* loadedSurface = IMG_Load(path);
		if (loadedSurface == NULL)
		{
			PINE_ENGINE_ERROR("Unable to load texture");
			return;
		}
		
		PINE_ENGINE_INFO("LOADED IMAGE");
		SDL_SetWindowIcon(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window, loadedSurface);
		SDL_FreeSurface(loadedSurface);
		m_IconSet = true;
	

		
	
	}
	void Renderer::CreateWhiteTexture() 
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererData.s_WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, m_RendererData.s_WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		GLuint color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		//set slot 0 to white texture
		m_RendererData.s_TextureSlots[0] = m_RendererData.s_WhiteTexture;
		//set all other texture slots to zero
		for (size_t i = 1; i < m_MaxTextureCount; i++)
		{
			m_RendererData.s_TextureSlots[i] = 0;
		}
	
	}
	GLuint Renderer::LoadTexture(const char* path)
	{
		

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path);
		if (loadedSurface == NULL)
		{
			PINE_ENGINE_ERROR("Unable to load texture");
			return 0;
		}
		else
		{
			PINE_ENGINE_INFO("LOADED IMAGE");
			GLuint texID;
			glCreateTextures(GL_TEXTURE_2D, 1, &texID);
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);

			SDL_FreeSurface(loadedSurface);
			return texID;
		}
		
	}


	
}