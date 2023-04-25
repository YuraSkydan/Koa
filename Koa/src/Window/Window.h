#pragma once
#include <Windows.h>
#include <vector>
#include <thread>

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Core/Defines.h"
#include "Pixel.h"

class Window
{
protected:
	int m_Width;
	int m_Height;

public: 
	Window(int width, int height);

	virtual void Update();

	void SetPixel(float x, float y, Color color);
	void SetPixel(const Vector2i& v, Color color);
	void SetPixel(const Vector2f& v, Color color);

    void DrawLine(int x0, int y0, int x1, int y1, Color color);
	void DrawLine(float x0, float y0, float x1, float y1, Color color);
	void DrawLine(const Vector2f& v0, const Vector2f& v1, Color color);

	void DrawTriangle(Vector2i verticies[3], Color color);
	void DrawTriangle(std::vector<Vector2i> verticies, Color color);

	void DrawVerticies(std::vector<Vector2f> verticies, Color color);
	void DrawVerticies(const std::vector<Vector3f>& verticies, Color color);

	void DrawCircle(int x, int y, int radius, Color color);
	void DrawCircle(const Vector2f& position, float radius, Color color);

	int GetWidth() const;
	int GetHeight() const;

	virtual void Clear() = 0;
	virtual void ClearColor(Color color) = 0;
	virtual void Draw() = 0;

	virtual void SetPixel(int x, int y, Color color) = 0;

	virtual Pixel GetPixel(int x, int y) = 0;
	virtual Pixel GetPixel(float x, float y) = 0;
	virtual Pixel GetPixel(const Vector2f& v) = 0;

	virtual void SetTitle(const wchar_t* title) = 0;
	virtual const wchar_t* GetTitle() const = 0;

	virtual ~Window();
};