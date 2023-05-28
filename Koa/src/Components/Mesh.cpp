#include <iostream>
#include <sstream>
#include <fstream>

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
	//Load mesh
	std::ifstream fileStream;
	fileStream.open(filename.data(), std::ifstream::in);
	
	if (fileStream.fail())
	{
		return;
	}

	m_Verticies.clear();

	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vector3f vertex;
			for (int i = 0; i < 3; i++)
			{
				iss >> vertex[i];
			}

			m_Verticies.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Vector3f normal;
			for (int i = 0; i < 3; i++)
			{
				iss >> normal[i];
			}

			m_Normals.push_back(normal.Normalized());
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			Vector2f uv;
			for (int i = 0; i < 2; i++)
			{
				iss >> uv[i];
			}

			m_TextureCoords.push_back(Vector2f( uv.x, 1 - uv.y));
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<int> f;
			int itrash, idx;
			iss >> trash;

			while (iss >> idx >> trash >> itrash >> trash >> itrash)
			{
				idx--;
				f.push_back(idx);
			}

			m_VerticiesFaces.push_back(f);
		}
	}

	m_MeshFilename = filename;
}

void Mesh::UnloadMesh()
{
	m_Verticies.clear();
	m_TextureCoords.clear();
	m_Normals.clear();
}

int Mesh::GetVerticiesAmount() const
{
	return m_Verticies.size();
}

int Mesh::GetFacesAmount() const
{
	return m_VerticiesFaces.size();
}

const std::string& Mesh::GetMeshFilename() const
{
	return m_MeshFilename;
}

const std::vector<int>& Mesh::GetFace(int index) const
{
	return m_VerticiesFaces[index];
}

const Vector3f& Mesh::GetVertex(int index) const
{
	return m_Verticies[index];
}

const std::vector<Vector3f>& Mesh::GetMeshVerticies() const
{
	return m_Verticies;
}