#include <cstring>
#include <algorithm>

#include "ConsoleWindow.h"
#include "../Math/VectorOperations.h"

Window::Window(int width, int height)
	: m_Width(width), m_Height(height)
{ }

void Window::Update()
{
	Draw();
}

void Window::SetPixel(float x, float y, Color color)
{
	int pixelX = (x * m_Width / 2.0f) + m_Width / 2.0f;
	int pixelY = (-y * m_Height / 2.0f) + m_Height / 2.0f;

	SetPixel(pixelX, pixelY, color);
}

void Window::SetPixel(const Vector2f& v, Color color)
{
	SetPixel(v.x, v.y, color);
}

void Window::SetPixel(const Vector2i& v, Color color)
{
	SetPixel(v.x, v.y, color);
}

void Window::DrawLine(int x0, int y0, int x1, int y1, Color color)
{
	int deltaX = abs(int(x1) - int(x0));
	int deltaY = abs(int(y1) - int(y0));

	int currentX = x0;
	int currentY = y0;

	//Draw Vertical Line
	if (deltaX == 0)
	{
		int sY = y0 < y1 ? 1 : -1;
		while (currentY != y1)
		{
			SetPixel(currentX, currentY, color);
			currentY += sY;
		}

		return;
	}

	//Draw Horizontal Line
	if (deltaY == 0)
	{
		int sX = x0 < x1 ? 1 : -1;
		while (currentX != x1)
		{
			SetPixel(currentX, currentY, color);
			currentX += sX;
		}
	}

	int sX = x0 < x1 ? 1 : -1;
	int sY = y0 < y1 ? 1 : -1;

	int error = deltaX - deltaY;

	while (currentX != x1 || currentY != y1)
	{
		SetPixel(currentX, currentY, color);

		int error2 = 2 * error;

		if (error2 > -deltaY)
		{
			error -= deltaY;
			currentX += sX;
		}

		if (error2 < deltaX)
		{
			error += deltaX;
			currentY += sY;
		}
	}

	SetPixel(currentX, currentY, color);
}

void Window::DrawLine(float x0, float y0, float x1, float y1, Color color)
{
	//int pixelX0 = (x0 * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	//int pixelY0 = (-y0 * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	//int pixelX1 = (x1 * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	//int pixelY1 = (-y1 * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	//DrawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);
}

void Window::DrawLine(const Vector2f& v0, const Vector2f& v1, Color color)
{
	DrawLine(v0.x, v0.y, v1.x, v1.y, color);
}

void Window::DrawTriangle(Vector2i verticies[3], Color color)
{
}

void Window::DrawTriangle(std::vector<Vector2i> verticies, Color color)
{
	std::sort(verticies.begin(), verticies.end(),
		[](const Vector2i& v1, const Vector2i& v2)
		{
			return v1.y < v2.y;
		});

	int totalHeight = verticies[2].y - verticies[0].y;
	for (int y = verticies[0].y; y <= verticies[1].y; y++)
	{
		int segmentHeight = verticies[1].y - verticies[0].y + 1;
		float alpha = (float)(y - verticies[0].y) / totalHeight;
		float beta = (float)(y - verticies[0].y) / segmentHeight;
		Vector2i A = verticies[0] + (verticies[2] - verticies[0]) * alpha;
		Vector2i B = verticies[0] + (verticies[1] - verticies[0]) * beta;

		if (A.x > B.x)
		{
			std::swap(A, B);
		}

		for (int j = A.x; j <= B.x; j++)
		{
			SetPixel(j, y, color);
		}
	}

	for (int y = verticies[1].y; y <= verticies[2].y; y++)
	{
		int segmentHeight = verticies[2].y - verticies[1].y + 1;
		float alpha = (float)(y - verticies[0].y) / totalHeight;
		float beta = (float)(y - verticies[1].y) / segmentHeight;
		Vector2i A = verticies[0] + (verticies[2] - verticies[0]) * alpha;
		Vector2i B = verticies[1] + (verticies[2] - verticies[1]) * beta;

		if (A.x > B.x)
		{
			std::swap(A, B);
		}

		for (int j = A.x; j <= B.x; j++)
		{
			SetPixel(j, y, color);
		}
	}
}

void Window::DrawVerticies(std::vector<Vector2f> verticies, Color color)
{
	//DrawLine(verticies[0], verticies[1], color);
	//DrawLine(verticies[1], verticies[2], color);
	//DrawLine(verticies[2], verticies[0], color);

	std::vector<Vector2i> convertedVerticies;

	for (auto& vertex : verticies)
	{
		int x = (vertex.x * m_Width / 2.0f) + m_Width / 2.0f;
		int y = (-vertex.y * m_Height / 2.0f) + m_Height / 2.0f;

		convertedVerticies.emplace_back(Vector2i(x, y));
	}

	DrawTriangle(convertedVerticies, color);

	//Vector2f center;
	//for (auto& vertex : verticies)
	//{
	//	center += vertex / 2.0f;
	//}
}

void Window::DrawVerticies(const std::vector<Vector3f>& verticies, Color color)
{
	for (auto it = verticies.begin(), end = verticies.end() - 1; it != end; ++it)
	{
		DrawLine(*it, *(it + 1), color);
	}

	DrawLine(*(verticies.rbegin()), *(verticies.begin()), color);

	Vector3f center;
	for (auto it = verticies.cbegin(), end = verticies.cend(); it != end; ++it)
	{
		center += (*it) / 2.0f;
	}
}

void Window::DrawCircle(int x, int y, int radius, Color color)
{
}

void Window::DrawCircle(const Vector2f& position, float radius, Color color)
{
}

int Window::GetWidth() const
{
	return m_Width;
}

int Window::GetHeight() const
{
	return m_Height;
}

Window::~Window() 
{ }