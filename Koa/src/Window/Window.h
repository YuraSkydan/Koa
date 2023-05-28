#pragma once
#include <Windows.h>
#include <vector>
#include <span>

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Core/Defines.h"
#include "Color.h"

//Remove later
#include <iostream>
#include <algorithm>
#include "../Components/Camera.h"

class Window
{
protected:
	int m_Width;
	int m_Height;

protected:
	int ConvertToWindowX(float x);
	int ConvertToWindowY(float y);
	int GetWindowBufferPosition(int x, int y);

public:
	Window(int width, int height);

	virtual void Update();

	void SetPixel(float x, float y, const Color& color);
	void SetPixel(const Vector2i& v, const Color& color);
	void SetPixel(const Vector2f& v, const Color& color);

	void DrawLine(int x0, int y0, int x1, int y1, const Color& color);
	void DrawLine(float x0, float y0, float x1, float y1, const Color& color);
	void DrawLine(const Vector2f& v0, const Vector2f& v1, const Color& color);

	//TODO: Move it to another class
	Vector3f Embed(const Vector2f& v, double fill = 1)
	{
		Vector3f ret;
		//for (int i = 3; i--; ret[i] = (i < 2 ? v[i] : fill));

		return ret;
	}

	Vector3f Barycentric(std::span<Vector2i> verticies, const Vector2i& point)
	{
		Vector3f u(verticies[2].x - verticies[0].x, verticies[1].x - verticies[0].x, verticies[0].x - point.x);
		Vector3f v(verticies[2].y - verticies[0].y, verticies[1].y - verticies[0].y, verticies[0].y - point.y);
		
		Vector3f result(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
	
		if (abs(result.z) < 1)
		{
			return Vector3f(-1.0f, 1.0f, 1.0f);
		}

		return Vector3f(1.0f - (result.x + result.y) / result.z, result.y / result.z, result.x / result.z);
	}

	void DrawTriangle(std::span<Vector2i> verticies, const Color& color);

	void DrawVerticies(std::span<Vector2f> verticies, const Color& color);
	void DrawVerticies(std::span<Vector3f> verticies, const Color& color);
	void DrawVerticies(const std::vector<Vector2f>& verticies, const Color& color);

	//Remove Later
	void DrawTriangle(std::span<Vector3i> verticies, const Color& color, Camera* camera)
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

		Vector2i p;
		for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
		{
			for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
			{
				SetPixel(p, color);
			}
		}
	}

	void DrawVerticies(std::span<Vector3f> verticies, const Color& color, Camera* camera)
	{

	}

	void DrawCircle(int x, int y, int radius, const Color& color);
	void DrawCircle(const Vector2f& position, float radius, const Color& color);

	int GetWidth() const;
	int GetHeight() const;

	virtual void Clear() = 0;
	virtual void ClearColor(const Color& color) = 0;
	virtual void Draw() = 0;

	virtual void SetPixel(int x, int y, const Color& color) = 0;

	virtual const Color& GetColor(int x, int y) = 0;
	virtual const Color& GetColor(float x, float y) = 0;
	virtual const Color& GetColor(const Vector2f& v) = 0;

	virtual void SetTitle(const wchar_t* title) = 0;
	virtual const wchar_t* GetTitle() const = 0;

	virtual ~Window();
};