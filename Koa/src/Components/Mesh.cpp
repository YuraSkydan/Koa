#include "Mesh.h"

Mesh::Mesh(Entity* owner)
	: Component(owner)
{ 
	//Front side
	m_Verticies.push_back({  0.5f, -0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f, -0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 0.0f });
										  
	m_Verticies.push_back({  0.5f, -0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 0.0f });
	m_Verticies.push_back({  0.5f,  0.5f, 0.0f });

	//Back side
	m_Verticies.push_back({ 0.5f,  -0.5f, 1.0f });
	m_Verticies.push_back({ -0.5f, -0.5f, 1.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 1.0f });

	m_Verticies.push_back({  0.5f, -0.5f, 1.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 1.0f });
	m_Verticies.push_back({  0.5f,  0.5f, 1.0f });

	//Left side
	m_Verticies.push_back({ -0.5f,  0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f, -0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 1.0f });

	m_Verticies.push_back({ -0.5f, -0.5f, 0.0f });
	m_Verticies.push_back({ -0.5f,  0.5f, 1.0f });
	m_Verticies.push_back({ -0.5f, -0.5f, 1.0f });
}

void Mesh::LoadMesh(std::string_view filename)
{
	m_MeshFilename = filename;

	//Load mesh
}

void Mesh::UnloadMesh()
{
	m_Verticies.clear();
	m_TextureCoords.clear();
	m_Normals.clear();
}

const std::string& Mesh::GetMeshFilename() const
{
	return m_MeshFilename;
}

const std::vector<Vector3f>& Mesh::GetMeshVerticies() const
{
	return m_Verticies;
}