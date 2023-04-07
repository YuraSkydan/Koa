#include "RaytracerExample.h"
#include "../Math/VectorOperations.h"
#include "../Components/Transform.h"
#include "../Core/Engine.h"
#include "../Core/Input.h"
#include "../Ray.h"
#include "../HitRecord.h"
#include "../Sphere.h"
#include "../Core/Time.h"
#include "../Metal.h"
#include "../Lambertian.h"

Vector3f RaytracerExample::Color(const Ray& ray, int depth)
{
	HitRecord record;
	bool hitAnything = false;
	double closest = FLT_MAX;

	for (auto& sphere : m_Spheres)
	{
		HitRecord tempRecord;
		if (sphere->Hit(ray, 0.001f, closest, tempRecord))
		{
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}

	if (hitAnything)
	{
		Ray scattered;
		Vector3f attenuation;
		if (depth < m_MaxDepth && record.materialPtr->Scatter(ray, record, attenuation, scattered))
		{
			return attenuation * Color(scattered, depth + 1);
		}

		return Vector3f(0, 0, 0);

		//Vector3f target = record.hitPoint + record.normal /*+ RandomInUnitSphere()*/;
		//return Vector3f(1.0f, 0.0f, 0.0f);
		//return 0.5f * Color(Ray(record.hitPoint, target - record.hitPoint));
	}
	else
	{
		Vector3f unitDirection = ray.GetDirection().Normalized();
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * Vector3f(1.0f, 1.0f, 1.0f) + t * Vector3f(0.5f, 0.7f, 1.0f);
	}
}

RaytracerExample::RaytracerExample()
{
	m_Scene = Engine::Get().GetScene();

	Entity* sphere = m_Scene->CreateEntity();
	sphere->GetTransform()->SetPosition(Vector3f::Forward * 10.0f + Vector3f::Down * 103.0f);
	Sphere* sphereComponent = sphere->AddComponent<Sphere>();
	sphereComponent->SetRadius(100.0f);

	sphereComponent->SetMaterial(std::make_unique<Lambertian>(Vector3f(0.4f, 0.8f, 0.0f)));
	m_Spheres.push_back(sphereComponent);

	sphere = m_Scene->CreateEntity();
	sphere->GetTransform()->SetPosition(Vector3f::Forward * 10.0f);
	sphereComponent = sphere->AddComponent<Sphere>();
	sphereComponent->SetRadius(3.0f);

	sphereComponent->SetMaterial(std::make_unique<Lambertian>(Vector3f(0.8f, 0.3f, 0.3f)));
	m_Spheres.push_back(sphereComponent);

	sphere = m_Scene->CreateEntity();
	sphere->GetTransform()->SetPosition(Vector3f::Forward * 10.0f + Vector3f::Right * 6.0f);
	sphereComponent = sphere->AddComponent<Sphere>();
	sphereComponent->SetRadius(3.0f);

	sphereComponent->SetMaterial(std::make_unique<Metal>(Vector3f(0.8f, 0.6f, 0.2f)));
	m_Spheres.push_back(sphereComponent);

	sphere = m_Scene->CreateEntity();
	sphere->GetTransform()->SetPosition(Vector3f::Forward * 10.0f + Vector3f::Right * -6.0f);
	sphereComponent = sphere->AddComponent<Sphere>();
	sphereComponent->SetRadius(3.0f);

	sphereComponent->SetMaterial(std::make_unique<Metal>(Vector3f(0.8f, 0.8f, 0.8f)));
	m_Spheres.push_back(sphereComponent);

	int sphereAmount = 0;
	for (int a = -sphereAmount; a < sphereAmount; a++)
	{
		for (int b = -sphereAmount; b < sphereAmount; b++)
		{
			float choosenMat = drand48();
			Vector3f center(a + 0.9f * drand48(), -0.3f, b + 0.9f * drand48());
			if ((center).Magnitude() > 0.9f)
			{
				sphere = m_Scene->CreateEntity();
				sphere->GetTransform()->SetPosition(center);
				sphereComponent = sphere->AddComponent<Sphere>();
				sphereComponent->SetRadius(0.5f);

				if (choosenMat < 0.8f)
				{
					sphereComponent->SetMaterial(std::make_unique<Lambertian>(Vector3f(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
				}
				else
				{
					sphereComponent->SetMaterial(std::make_unique<Metal>(Vector3f(0.5f * (1 + drand48()), 0.5f * (1.0f + drand48()), 0.5f * drand48())));
				}

				m_Spheres.push_back(sphereComponent);
			}
		}
	}
}

void RaytracerExample::OnUpdate()
{
	Window* window = Engine::Get().GetWindow();

	Color::Shade shade = Color::Shade::None;

	float xStep = 2.0f / float(window->GetConsoleBufferSize().X);
	float yStep = 2.0f / float(window->GetConsoleBufferSize().Y);

	static float cameraAngle = 0;

	for (float x = -1.0f; x < 1.0f; x += xStep)
	{
		shade = Color::Shade((x + 1.0f) / 2.0f * int(Color::Shade::Count));
		for (float y = -1.0f; y < 1.0f; y += yStep)
		{
			Vector3ui color((x + 1.0f) * 128.0f, (y + 1.0f) * 128.0f, 0);
			//Vector3ui color(200, 200, 200);
			//window->SetPixel(x, y, Color(Color::White, shade));
			//window->SetPixel(x, y, color);
			
			Vector3f zAxis = Vector3f(sin(cameraAngle), 0.0f, cos(cameraAngle));
			Vector3f xAxis = Cross(Vector3f(0.0f, 1.0f, 0.0f), zAxis);
			
			Vector3f direction = x * xAxis + Vector3f(0.0f, y, 0.0f) + zAxis;
			Ray ray(m_PlayerPosition, direction.Normalized());
			HitRecord record;

			color = Color(ray, 0) * 255.0f;
			window->SetPixel(x, y, color);
		}
	}

	if (Input::IsKeyPressed(Key::Right))
	{
		//m_PlayerPosition.x += Time::DeltaTime() * 5;
		cameraAngle += Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::Left))
	{
		//m_PlayerPosition.x -= Time::DeltaTime() * 5;
		cameraAngle -= Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::Up))
	{
		m_PlayerPosition.y += Time::DeltaTime() * 5;
	}
	if (Input::IsKeyPressed(Key::Down))
	{
		m_PlayerPosition.y -= Time::DeltaTime() * 5;
	}
	if (Input::IsKeyPressed(Key::W))
	{
		m_PlayerPosition.z += Time::DeltaTime() * 5;
	}
	if (Input::IsKeyPressed(Key::S))
	{
		m_PlayerPosition.z -= Time::DeltaTime() * 5;
	}
	if (Input::IsKeyPressed(Key::Space))
	{
		m_MaxDepth++;
	}
	if (Input::IsKeyPressed(Key::Shift))
	{
		m_MaxDepth--;
	}
}