#include "Renderer.h"

#include <array>
#include "../Core/Engine.h"
#include "../Window/Window.h"
#include "../Math/VectorOperations.h"
#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/CircleRenderer.h"
#include "../Components/Renderers/LineRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"
#include "../Components/Mesh.h"

const std::array<Vector2f, 6> squareVerticies =
{
	Vector2f{ -0.5f, -0.5f },
	Vector2f{ -0.5f,  0.5f },
	Vector2f{  0.5f, -0.5f },
		  		  
	Vector2f{  0.5f, -0.5f },
	Vector2f{  0.5f,  0.5f },
	Vector2f{ -0.5f,  0.5f }
};

const std::array<Vector2f, 2> lineVerticies =
{
	Vector2f{ -0.5f, 0.0f },
	Vector2f{  0.5f, 0.0f }
};

void Renderer::SetWindowContext(Window* windowContext)
{
	s_WindowContext = windowContext;
}

void Renderer::StartRendering(const Camera* camera)
{
	s_Camera = camera;
}

void Renderer::DrawSprite(const SpriteRenderer* spriteRenderer)
{
	std::array<Vector2f, 6> verticies(squareVerticies);
	Matrix4x4f transformMatrix = spriteRenderer->GetTransform()->GetTransformMatrix();
	for (auto& vertex : verticies)
	{
		Vector4f projection = transformMatrix * s_Camera->GetProjectionMatrix() * Vector4f(vertex, 1.0f, 1.0f);
	
		projection /= projection.w;
		vertex.x = projection.x;
		vertex.y = projection.y;
	}

	Engine::Get().GetWindow()->DrawVerticies(std::vector<Vector2f>(verticies.begin(), verticies.begin() + 3), spriteRenderer->GetColor());
	Engine::Get().GetWindow()->DrawVerticies(std::vector<Vector2f>(verticies.begin() + 3, verticies.end()), spriteRenderer->GetColor());
}

void Renderer::DrawCircle(const CircleRenderer* circleRenderer)
{
	//Vector2f position = circleRenderer->GetTransform()->GetPosition();
	//Engine::Get().GetWindow()->DrawCircle(position, circleRenderer->GetRadius(), circleRenderer->GetColor());
}

void Renderer::DrawLine(const LineRenderer* lineRenderer)
{
	Matrix4x4f transformMatrix = lineRenderer->GetTransform()->GetTransformMatrix();
	Vector4f start = transformMatrix * Vector4f(lineVerticies[0], 1.0f, 1.0f);
	Vector4f end = transformMatrix * Vector4f(lineVerticies[1], 1.0f, 1.0f);

	start /= start.w;
	end /= end.w;

	Engine::Get().GetWindow()->DrawLine(Vector2f(start.x, start.y), Vector2f(end.x, end.y), lineRenderer->GetColor());
}

void Renderer::DrawPixel(const PixelRenderer* pixelRenderer)
{

}

void Renderer::DrawMesh(const Mesh* mesh)
{
	const Matrix4x4f projection = s_Camera->GetProjectionMatrix();
	const std::vector<Vector3f>& meshVerticies = mesh->GetMeshVerticies();
	
	std::array<Vector3f, 3> polygon;
	auto polygonIt = polygon.begin();

	for (int i = 0; i < mesh->GetFacesAmount(); i++)
	{
		const std::vector<int>& face = mesh->GetFace(i);
		for (const auto& vIndex : face)
		{
			Matrix4x4f transformMatrix = mesh->GetTransform()->GetTransformMatrix();
			Vector4f v = projection * transformMatrix * Vector4f(mesh->GetVertex(vIndex), 1.0f);

			if (v.w != 0)
			{
				v /= v.w;
			}

			polygonIt->x = v.x;
			polygonIt->y = v.y;
			polygonIt->z = v.z;

			polygonIt++;
			if (polygonIt == polygon.end())
			{
				Engine::Get().GetWindow()->DrawVerticies(polygon, vIndex);
				polygonIt = polygon.begin();
			}
		}
	}
}