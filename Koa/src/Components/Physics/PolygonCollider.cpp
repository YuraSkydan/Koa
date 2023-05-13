#include "PolygonCollider.h"

void PolygonCollider::SetShape()
{
	m_Shape.Set(m_Vertices.data(), m_Vertices.size());
	m_FixtureDef.shape = &m_Shape;
}

PolygonCollider::PolygonCollider(Entity* owner)
	: Collider(owner)
	, Component(owner)
{
	m_Vertices.push_back({ -0.5f, -0.5f });
	m_Vertices.push_back({ 0.5f, -0.5f });
	m_Vertices.push_back({ 0.0f,  0.5f });
}

void PolygonCollider::Start()
{
	SetShape();
	Collider::Start();
}

void PolygonCollider::AddVertex(const Vector2f& vertexPos)
{
	m_Vertices.push_back({ vertexPos.x, vertexPos.y });
	ResetShape();
}

void PolygonCollider::RemoveVertex(const Vector2f& vertexPos)
{
	for (auto it = m_Vertices.begin(); it != m_Vertices.end(); ++it)
	{
		if (*it == b2Vec2{ vertexPos.x, vertexPos.y })
		{
			it = m_Vertices.erase(it);
			break;
		}
	}

	ResetShape();
}

void PolygonCollider::RemoveVertex(const std::vector<b2Vec2>::const_iterator& vertex)
{
	m_Vertices.erase(vertex);
	ResetShape();
}

void PolygonCollider::SetVerices(const std::vector<b2Vec2>& verticies)
{
	m_Vertices = verticies;
	ResetShape();
}