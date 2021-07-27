#include "RendererComponent.h"

namespace Pine
{


	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size= p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture = 0;
		_Quad->s_Name = "";
		_Quad->s_ID = 0;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const int p_ID, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture = 0;
		_Quad->s_Name = "";
		_Quad->s_ID = p_ID;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const glm::vec4& p_Color, const std::string p_Name, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Color;
		_Quad->s_Texture = 0;
		_Quad->s_Name = p_Name;
		_Quad->s_ID = 0;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* p_Tex, const glm::vec4& p_Col, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Col;
		_Quad->s_Texture = GetTexture(p_Tex);
		_Quad->s_Name = "";
		_Quad->s_ID = 0;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}
	


	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* p_Tex, const glm::vec4& p_Col, const int p_ID, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Col;
		_Quad->s_Texture = GetTexture(p_Tex);
		_Quad->s_Name = "";
		_Quad->s_ID = p_ID;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}
	void RendererComponent::DrawQuad(const glm::vec2& p_Pos, const glm::vec2& p_Size, const char* p_Tex, const glm::vec4& p_Col, const std::string p_Name, LayerLevel p_Level)
	{
		std::shared_ptr<Quad> _Quad = std::make_shared<Quad>();
		_Quad->s_Pos = p_Pos;
		_Quad->s_Size = p_Size;
		_Quad->s_Color = p_Col;
		_Quad->s_Texture = GetTexture(p_Tex);
		_Quad->s_Name = p_Name;
		_Quad->s_ID = 0;
		_Quad->s_LayerLevel = p_Level;
		m_Quads.push_back(_Quad);
	}

	void RendererComponent::LoadTexture(std::string p_Name, const char* p_TextureLocation) 
	{

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(p_TextureLocation);
		if (loadedSurface == NULL)
		{
			PINE_ENGINE_ERROR("Unable to load texture");
			return;
		}
		
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
			

		if (!std::get<bool>(m_Textures.try_emplace(p_Name, texID)))
		{
			PINE_ENGINE_WARN("Texture '{0}' already exists", p_Name);
		}
		PINE_ENGINE_WARN("Texture '{0}' added {1}", p_Name, texID);
	
	}

	GLuint RendererComponent::GetTexture(std::string p_Name)
	{
		for (auto q : m_Textures)
		{
			if (q.first == p_Name)
			{
				PINE_ENGINE_WARN("Tex {0} at {1}", q.first, q.second);
				return --q.second;

			}
		}
	}
	std::vector<GLuint> RendererComponent::GetAllTextures()
	{
		std::vector<GLuint> _Textures;

		for (auto tex : m_Textures)
		{

			_Textures.push_back(tex.second);
			PINE_ENGINE_WARN("PUSHING");
		}

		return _Textures;
		
	}
	void RendererComponent::Render() {}

	void RendererComponent::Update(float p_StepTime) {}

	void RendererComponent::HitTest(std::string p_ObjectName)
	{

		GetQuad(p_ObjectName);
	}

	bool RendererComponent::CheckCollision(glm::vec2 _PosOne, glm::vec2 _PosTwo, glm::vec2 p_SizeOne, glm::vec2 p_SizeTwo) // AABB - AABB collision
	{
		// collision x-axis?
		bool collisionX = _PosOne.x + p_SizeOne.x >= _PosTwo.x &&
			_PosTwo.x + p_SizeTwo.x >= _PosOne.x;
		// collision y-axis?
		bool collisionY = _PosOne.y + p_SizeOne.y >= _PosTwo.y &&
			_PosTwo.y + p_SizeTwo.y >= _PosOne.y;
		// collision only if on both axes
		return collisionX && collisionY;
	}
	float RendererComponent::area(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3)
	{
		return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
	}
	bool RendererComponent::PointInTri(const glm::vec2& p, const glm::vec2& p0, const  glm::vec2& p1, const  glm::vec2& p2)
	{
		float A = area(p0, p1, p2);
		float A1 = area(p, p0, p1);
		float A2 = area(p, p1, p2);
		float A3 = area(p, p2, p0);
		

		 

		return (A == A1 + A2 + A3);
	}


	bool RendererComponent::CheckWithTriangleCollision(glm::vec2 _PosOne, glm::vec2 _PosTwo, glm::vec2 p_SizeOne, glm::vec2 p_SizeTwo)
	{
		glm::vec4 _PlayerTransVertices[4];

		glm::vec4 Vertices[4] = {
		{ _PosOne.x, _PosOne.y, 0.0f, 0.0f },
		{  _PosOne.x + p_SizeOne.x, _PosOne.y, 0.0f, 0.0f },
		{  _PosOne.x + p_SizeOne.x,  _PosOne.y + p_SizeOne.y, 0.0f, 0.0f },
		{ _PosOne.x, _PosOne.y + p_SizeOne.y, 0.0f, 0.0f }
		};

		glm::vec4 PillarVertices[4] = {
		{ _PosTwo.x, _PosTwo.y, 0.0f, 0.0f },
		{  _PosTwo.x + p_SizeTwo.x, _PosTwo.y, 0.0f, 0.0f },
		{  _PosTwo.x + p_SizeTwo.x,  _PosTwo.y + p_SizeTwo.y, 0.0f, 0.0f },
		{ _PosTwo.x, _PosTwo.y + p_SizeTwo.y, 0.0f, 0.0f }
		};

		for (int i = 0; i < 3; i++)
		{
			glm::vec2 tri[3];

			PillarVertices[2].x -= 35;


			tri[0] = { PillarVertices[0].x, PillarVertices[0].y };
			tri[1] = { PillarVertices[1].x, PillarVertices[1].y };
			tri[2] = { PillarVertices[2].x, PillarVertices[2].y };

			if (PointInTri(_PosOne, tri[0], tri[1], tri[2]))
				return true;

		}
		return false;
	 
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

	std::shared_ptr<RendererComponent::Quad> RendererComponent::GetQuad(std::string p_Name) 
	{
	//std::vector<std::shared_ptr<Quad>>::iterator it = m_Quads.begin();
		for (auto q : m_Quads) 
		{
			if (q->s_Name == p_Name)
			{
				return q;

			}
		}
		
	return std::shared_ptr<RendererComponent::Quad>(nullptr);
	 
	}
}