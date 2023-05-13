#include "PixelPhysicsGrid.h"
#include "../Components/Physics/PixelPhysics.h"
#include "../Components/Transform.h"

void PixelPhysicsGrid::ResizeGrid()
{
	m_Width = m_UpRightBorder.x - m_DownLeftBorder.x;
	m_Height = m_UpRightBorder.y - m_DownLeftBorder.y;

	m_PhysicsPixels.resize(m_Width * m_Height);
}

PixelPhysicsGrid::PixelPhysicsGrid(const Vector2i& downLeftBorder, const Vector2i& upRightBorder)
	: m_DownLeftBorder(downLeftBorder), m_UpRightBorder(upRightBorder)
{
	ResizeGrid();
}

void PixelPhysicsGrid::Simulate()
{
	for (int x = 0; x < m_Width; x++)
	{
		for(int y = 0; y < m_Height; y++)
		{
			PixelPhysics* physicsPixel = GetPixelPhysics(x, y);
			if (physicsPixel != nullptr)
			{
				Transform* pixelTransform = physicsPixel->GetTransform();
				Vector3f position = pixelTransform->GetPosition();
			
				switch (physicsPixel->type)
				{
				case PixelPhysics::ObjectType::Sand:
					while (abs(physicsPixel->velocity.y) >= 1.0f)
					{
						int sign = signbit(physicsPixel->velocity.y) ? 1.0f : -1.0f;
						if (GetPixelPhysics(position.x, position.y + sign) != nullptr)
						{
							if (GetPixelPhysics(position.x - 1, position.y + sign) == nullptr)
							{
								position.x -= 1;
							}
							else if (GetPixelPhysics(position.x + 1, position.y + sign) == nullptr)
							{
								position.x += 1;
							}
						}
						position.y -= sign;
						physicsPixel->velocity.y += sign;
					}

					/*while (abs(physicsPixel->velocity.x) >= 1.0f)
					{
						
					}*/
					break;
				case PixelPhysics::ObjectType::Water:
					break;
				case PixelPhysics::ObjectType::Fire:
					break;
				}

				if (position.y < 0)
				{
					position.y = 0;
				}

				pixelTransform->SetPosition(position);
				AddPhysicsPixel(physicsPixel);
			}
		}
	}
}

void PixelPhysicsGrid::AddPhysicsPixel(PixelPhysics* pixelPhysics)
{
	Vector3f position = pixelPhysics->GetTransform()->GetPosition();

	if ((position.y < 0 || position.y >= m_Height) ||
		(position.x < 0 || position.x >= m_Width))
	{
		return;
	}

	int index = m_Width * position.y + position.x;
	m_PhysicsPixels[index] = pixelPhysics;
}

void PixelPhysicsGrid::SetDownLeftBorder(const Vector2i& downLeftBorder)
{
	m_DownLeftBorder = downLeftBorder;
	ResizeGrid();
}

void PixelPhysicsGrid::SetUpRightBorder(const Vector2i& upRightBorder)
{
	m_UpRightBorder = upRightBorder;
	ResizeGrid();
}

PixelPhysics* PixelPhysicsGrid::GetPixelPhysics(int x, int y)
{
	if ((x < m_DownLeftBorder.x || x >= m_UpRightBorder.x) ||
		(y < m_DownLeftBorder.y || y >= m_UpRightBorder.y))
	{
		return nullptr;
	}

	int position = m_Width * y + x;

	return m_PhysicsPixels[position];
}

const PixelPhysics* PixelPhysicsGrid::GetPixelPhysics(int x, int y) const
{
	if ((x < m_DownLeftBorder.x || x >= m_UpRightBorder.x) ||
		(y < m_DownLeftBorder.y || y >= m_UpRightBorder.y))
	{
		return nullptr;
	}

	int position = m_Width * y + x;

	return m_PhysicsPixels[position];
}

const Vector2i& PixelPhysicsGrid::GetDownLeftBorder() const
{
	return m_DownLeftBorder;
}

const Vector2i& PixelPhysicsGrid::GetUpRightBorder() const
{
	return m_UpRightBorder;
}