#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>
#include <glew.h>
#include "Log.h"
#include <memory>
#include <algorithm>
#include <gtc/matrix_transform.hpp>
#include "SDL.h"
#include <SDL_image.h>

//#include "Shader.h"

namespace Pine
{
	
	class RendererComponent : public Component
	{
		
	public:

		enum LayerLevel
		{
			NONE,
			TOP,
			BOTTOM

		};
		RendererComponent(std::string p_Name) : Component(p_Name) {};
		struct Quad
		{
			glm::vec2		s_Pos		= { 0.0f, 0.0f};
			glm::vec2		s_Size		= { 0.0f, 0.0f };
			glm::vec2		s_Rotation	= { 0.0f, 0.0f };
			glm::vec4		s_Color		= { 0.0f, 0.0f, 0.0f, 1.0f };
			int				s_Texture	= 0;
			int				s_QuadID	= 0;
			std::string		s_Name		= "";  
			int				s_ID		= 0;
			LayerLevel		s_LayerLevel = LayerLevel::NONE;
		};
		
		void Render() override;

		void Update(float p_StepTime) override;

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, LayerLevel p_Level);

		//void SetShader(std::string p_Name, SourceShader& p_Shader);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const int p_ID, LayerLevel p_Level);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, std::string p_Name, LayerLevel p_Level);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* tex, const glm::vec4& p_Col, LayerLevel p_Level);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* tex, const glm::vec4& p_Col, const int p_ID, LayerLevel p_Level);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* tex, const glm::vec4& p_Col, std::string p_Name, LayerLevel p_Level);

		std::weak_ptr<Quad> GetQuad(int p_ID);

		std::shared_ptr<Quad> GetQuad(std::string p_Name);

		void HitTest(std::string p_ObjectName);

		bool CheckCollision(glm::vec2 _PosOne, glm::vec2 _PosTwo, glm::vec2 p_SizeOne, glm::vec2 p_SizeTwo);// AABB - AABB collision

		bool CheckWithTriangleCollision(glm::vec2 _PosOne, glm::vec2 _PosTwo, glm::vec2 p_SizeOne, glm::vec2 p_SizeTwo);

		float area(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2);

		bool PointInTri(const glm::vec2& p, const glm::vec2& p0, const  glm::vec2& p1, const  glm::vec2& p2);
		
		//NOTE Textures need to be rgba8. If texture doesnt load, open in photoshope or gimp and save as a rgba8 png
		void LoadTexture(std::string p_Name, const char* p_TextureLocation);

		GLuint GetTexture(std::string p_Name);

		std::vector<GLuint> GetAllTextures();

		void DeleteQuad(std::shared_ptr<Quad> p_Quad);

		void DeleteQuad(std::string p_QuadName);
		//unused
		std::vector<std::weak_ptr<Quad>> GetQuads();

		std::vector<std::shared_ptr<Quad>> GetAllQuads() { return m_Quads; }

		//std::unordered_map<std::string, int> m_Shaders;

		std::unordered_map<std::string, GLuint> m_Textures;

	private:

		std::vector<std::shared_ptr<Quad>> m_Quads;
	};
}