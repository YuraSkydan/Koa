#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "../Math/Vector3.h"

class Mesh : public Component
{
private:
	std::string m_MeshFilename;
	std::vector<Vector3f> m_Verticies;
	std::vector<Vector3f> m_TextureCoords;
	std::vector<Vector3f> m_Normals;

public:
	Mesh(Entity* owner);

	void LoadMesh(std::string_view filename);
	void UnloadMesh();

	const std::string& GetMeshFilename() const;
	const std::vector<Vector3f>& GetMeshVerticies() const;
};