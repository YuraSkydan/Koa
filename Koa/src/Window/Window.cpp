#include <cstring>
#include <algorithm>

#include "ConsoleWindow.h"
#include "../Math/VectorOperations.h"

int Window::ConvertToWindowX(float x)
{
	return (x * m_Width / 2.0f) + (m_Width / 2.0f);
}

int Window::ConvertToWindowY(float y)
{
	return (-y * m_Height / 2.0f) + (m_Height / 2.0f);
}

Window::Window(int width, int height)
	: m_Width(width), m_Height(height)
{ }

void Window::Update()
{
	Draw();
}

void Window::SetPixel(float x, float y, const Color& color)
{
	int pixelX = ConvertToWindowX(x);
	int pixelY = ConvertToWindowY(y);

	SetPixel(pixelX, pixelY, color);
}

void Window::SetPixel(const Vector2f& v, const Color& color)
{
	SetPixel(v.x, v.y, color);
}

void Window::SetPixel(const Vector2i& v, const Color& color)
{
	SetPixel(v.x, v.y, color);
}

void Window::DrawLine(int x0, int y0, int x1, int y1, const Color& color)
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

void Window::DrawLine(float x0, float y0, float x1, float y1, const Color& color)
{
	int pixelX0 = ConvertToWindowX(x0);
	int pixelY0 = ConvertToWindowY(y0);

	int pixelX1 = ConvertToWindowX(x1);
	int pixelY1 = ConvertToWindowY(y1);

	DrawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);
}

void Window::DrawLine(const Vector2f& v0, const Vector2f& v1, const Color& color)
{
	DrawLine(v0.x, v0.y, v1.x, v1.y, color);
}

void Window::DrawTriangle(std::span<Vector2i> verticies, const Color& color)
{
	Vector2i bboxmin(m_Width - 1, m_Height - 1);
	Vector2i bboxmax(0, 0);
	Vector2i clamp(m_Width - 1, m_Height - 1);

	for (int i = 0; i < 3; i++)
	{
		bboxmin.x = max(0, min(bboxmin.x, verticies[i].x));
		bboxmin.y = max(0, min(bboxmin.y, verticies[i].y));

		bboxmax.x = min(clamp.x, max(bboxmax.x, verticies[i].x));
		bboxmax.y = min(clamp.y, max(bboxmax.y, verticies[i].y));
	}

	Vector2i point;
	for (point.x = bboxmin.x; point.x <= bboxmax.x; point.x++)
	{
		for (point.y = bboxmin.y; point.y <= bboxmax.y; point.y++)
		{
			Vector3f bcScreen = Barycentric(verticies, point);
			if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0)
			{
				continue;
			}

			SetPixel(point.x, point.y, color);
		}
	}

	{
		//std::sort(verticies.begin(), verticies.end(),
		//	[](const Vector2i& v1, const Vector2i& v2)
		//	{
		//		return v1.y < v2.y;
		//	});

		//int totalHeight = verticies[2].y - verticies[0].y;

		//if (totalHeight == 0)
		//{
		//	return;
		//}

		//for(int y = verticies[0].y; y <= verticies[1].y; y++)
		//{
		//	int segmentHeight = verticies[1].y - verticies[0].y + 1;
		//	float alpha = (float)(y - verticies[0].y) / totalHeight;
		//	float beta = (float)(y - verticies[0].y) / segmentHeight;
		//	Vector2i A = verticies[0] + (verticies[2] - verticies[0]) * alpha;
		//	Vector2i B = verticies[0] + (verticies[1] - verticies[0]) * beta;

		//	if (A.x > B.x)
		//	{
		//		std::swap(A, B);
		//	}

		//	for (int j = A.x; j <= B.x; j++)
		//	{
		//		SetPixel(j, y, color);
		//	}
		//}

		//for (int y = verticies[1].y; y <= verticies[2].y; y++)
		//{
		//	int segmentHeight = verticies[2].y - verticies[1].y + 1;
		//	float alpha = (float)(y - verticies[0].y) / totalHeight;
		//	float beta = (float)(y - verticies[1].y) / segmentHeight;
		//	Vector2i A = verticies[0] + (verticies[2] - verticies[0]) * alpha;
		//	Vector2i B = verticies[1] + (verticies[2] - verticies[1]) * beta;

		//	if (A.x > B.x)
		//	{
		//		std::swap(A, B);
		//	}

		//	for (int j = A.x; j <= B.x; j++)
		//	{
		//		SetPixel(j, y, color);
		//	}
		//}
	}
}

void Window::DrawVerticies(std::span<Vector2f> verticies, const Color& color)
{

}

void Window::DrawVerticies(std::span<Vector3f> verticies, const Color& color)
{
	std::vector<Vector2i> converted(verticies.size());
	auto it = converted.begin();

	for (auto& v : verticies)
	{
		int x = ConvertToWindowX(v.x);
		int y = ConvertToWindowY(v.y);

		*it = Vector2i(x, y);
		it++;
	}

	DrawTriangle(converted, color);
}

void Window::DrawVerticies(const std::vector<Vector2f>& verticies, const Color& color)
{
	std::vector<Vector2i> converted(verticies.size());
	auto it = converted.begin();

	for (auto& v : verticies)
	{
		int x = ConvertToWindowX(v.x);
		int y = ConvertToWindowY(v.y);

		*it = Vector2i(x, y);
		it++;
	}

	DrawTriangle(converted, color);
}

void Window::DrawCircle(int x, int y, int radius, const Color& color)
{
}

void Window::DrawCircle(const Vector2f& position, float radius, const Color& color)
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