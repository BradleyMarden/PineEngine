#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>
#include <glew.h>
#include <memory>
#include <algorithm>
namespace Pine
{
	
	class RendererComponent : public Component
	{
		
	public:
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
		};

		void Render() override;

		void Update(float p_StepTime) override;

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const int p_ID);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, std::string p_Name);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint tex);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint tex, const int p_ID);

		void DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint tex, std::string p_Name);

		std::weak_ptr<Quad> GetQuad(int p_ID);

		std::shared_ptr<Quad> GetQuad(std::string p_Name);

		void HitTest(std::string p_ObjectName);

		bool CheckCollision(glm::vec2 _PosOne, glm::vec2 _PosTwo, glm::vec2 p_SizeOne, glm::vec2 p_SizeTwo);// AABB - AABB collision

		void DeleteQuad(std::shared_ptr<Quad> p_Quad);

		void DeleteQuad(std::string p_QuadName);
		//unused
		std::vector<std::weak_ptr<Quad>> GetQuads();

		std::vector<std::shared_ptr<Quad>> GetAllQuads() { return m_Quads; }

	private:

		std::vector<std::shared_ptr<Quad>> m_Quads;
	};
}