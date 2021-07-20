#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Log.h"
#include "window.h"
#include <glm.hpp>
#include <glew.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

namespace Pine {
#define OPENGL(x) Renderer::GLClearError();\
								Renderer::GLCheckError();
/*#if DEBUG
#define GLCheckError() GLERROR()
#else
#define GLCheckError()
#endif
	*/


	//renderer will only be allowed to, 
	class Renderer
	{

	public:
		
		//SDL_Renderer* GetRenderer() { return m_SDL_Renderer; }

		static void GLClearError();
		
		static void GLCheckError();

		static void LinkShaders();
	
        //load scene from file.
		static void InitRendering();

		static void BeginBatch();

		static void EndBatch();

		static void Shutdown();

		static void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color);
        
        static void LoadScene(const char* p_FilePath);

		static void RenderUI();

		static void Render();
	
        static void CreateQuad(const char* p_Name, int p_Width, int p_Height);

        static void CreateQuad(const char* p_Name, int p_Width, int p_Height,GLint m_Texture);

        static void LoadTextureMap(const char* p_FilePath);

		static void SetWindowIcon(const char* path);
		//Returns true if icon has been set.
		inline static bool GetIconSet() { return m_IconSet; }

		static GLuint LoadTexture(const char* path);
        
        static void Flush();
		inline static bool HasInit() { return hasRun; };
		static void ResetStats();
		static 	bool limitFPS;

	private:

		static const size_t m_MaxQuadCount = 1000;					//per flush
		static const size_t m_MaxVertexCount = m_MaxQuadCount * 4;	//each quad has 4 vertex
		static const size_t m_MaxIndexCount = m_MaxQuadCount * 6;	//each quad has 6 index
		static const size_t m_MaxTextureCount = 32;					//max texture slot on MY current system. Will be different depending on the device. Need to add some checking in a future build
		static SDL_Renderer** renderer;
		static bool hasRun;
		static bool m_IconSet;

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

		enum  RenderCategory		//define the category of render, needs to be a 
									//bitset as an event can be more than one category
		{
			None = 0,
			Sprite = SETBIT(0),			//this equates to '0000 0000 0000 0000 0000 0000 0000 0001' 32 bits or 4 bytes. The size of a int
			UI = SETBIT(1),				//this equates to '0000 0000 0000 0000 0000 0000 0000 0010'
			Text = SETBIT(2),			//this equates to '0000 0000 0000 0000 0000 0000 0000 0100'
			Background = SETBIT(3)		//this equates to '0000 0000 0000 0000 0000 0000 0001 0000'
		};


		

		//list of shaders to be loaded that will be iterated through at the start and stored in a vector.
	};
}
