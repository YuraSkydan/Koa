#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

class Mesh : public Component
{
private:
	std::string m_MeshFilename;
	std::vector<Vector3f> m_Verticies;
	std::vector<Vector2f> m_TextureCoords;
	std::vector<Vector3f> m_Normals;
	std::vector<std::vector<int>> m_VerticiesFaces;
	std::vector<int> m_FacetTexture;
	std::vector<int> m_FacetNormals;

public:
	Mesh(Entity* owner);

	void LoadMesh(std::string_view filename);
	void UnloadMesh();

	int GetVerticiesAmount() const;
	int GetFacesAmount() const;

	const std::string& GetMeshFilename() const;
	const std::vector<int>& GetFace(int index) const;
	const Vector3f& GetVertex(int index) const;
	const std::vector<Vector3f>& GetMeshVerticies() const;
};