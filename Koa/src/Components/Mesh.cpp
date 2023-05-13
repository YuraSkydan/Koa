#include "Mesh.h"

Mesh::Mesh(Entity* owner)
	: Component(owner)
{ }

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