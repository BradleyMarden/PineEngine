#include "RendererComponent.h"

namespace Pine
{


	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color) 
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size= p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture= 0;
		_Quad->s_Name = "";
		_Quad->s_ID = 0;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const int p_ID)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture = 0;
		_Quad->s_Name = "";
		_Quad->s_ID = p_ID;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const std::string p_Name)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture = 0;
		_Quad->s_Name = p_Name;
		_Quad->s_ID = 0;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint p_Tex)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = {0.0f, 0.0f, 0.0f, 1.0f};
		_Quad->s_Texture = p_Tex;
		_Quad->s_Name = "";
		_Quad->s_ID = 0;
		m_Quads.push_back(_Quad);
	}
	


	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint p_Tex, const int p_ID)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
		_Quad->s_Texture = p_Tex;
		_Quad->s_Name = "";
		_Quad->s_ID = p_ID;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const GLuint p_Tex, const std::string p_Name)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
		_Quad->s_Texture = p_Tex;
		_Quad->s_Name = p_Name;
		_Quad->s_ID = 0;
		m_Quads.push_back(_Quad);
	}


	 void RendererComponent::Render() {}

	 void RendererComponent::Update(float p_StepTime) {}

	 void RendererComponent::HitTest()
	 {


	 }

	 void RendererComponent::DeleteQuad(std::shared_ptr<Quad> p_Quad)
	 {
		
		 std::vector<std::shared_ptr<Quad>>::iterator it;// = m_Quads.begin
		 it = std::find(m_Quads.begin(), m_Quads.end(), p_Quad);
	 
		 if (it != m_Quads.end())
		 {
			 //remove quad;
			 m_Quads.erase(it);
		 }
	 }

	 void RendererComponent::DeleteQuad(std::string p_QuadName)
	 {

		 std::vector<std::shared_ptr<Quad>>::iterator it = m_Quads.begin();
		 while (it != m_Quads.end())
		 {
			 int index = std::distance(m_Quads.begin(), it);
			 if (it[index]->s_Name == p_QuadName)
			 {
				 m_Quads.erase(it);
			 }
		 }
		 if (it != m_Quads.end())
		 {
			 //remove quad;
			 m_Quads.erase(it);
		 }
	 }

	 std::vector<std::weak_ptr<RendererComponent::Quad>> RendererComponent::GetQuads() 
	 {
		
		 std::vector<std::weak_ptr<Quad>> quad;
		 //lambda
		 std::transform(m_Quads.begin(), m_Quads.end(), quad.begin(), 
			 [](std::weak_ptr<Quad> weakPtr){ return weakPtr.lock(); });

		 return quad;
	 
	 }
}