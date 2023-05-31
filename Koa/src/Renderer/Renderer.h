#pragma once
#include "../Math/Vector2.h"
#include "../Window/Color.h"
#include "../Window/Window.h"

class SpriteRenderer;
class CircleRenderer;
class LineRenderer;
class PixelRenderer;
class Mesh;

class Renderer
{
private:
	inline static Window* s_WindowContext = nullptr;
	inline static const Camera* s_Camera = nullptr;

public:
	//void SetPixel(int x, int y, const Color& color);
	//void SetPixel(float x, float y, const Color& color);
	//void SetPixel(const Vector2i& v, const Color& color);
	//void SetPixel(const Vector2f& v, const Color& color);

	//void DrawLine(int x0, int y0, int x1, int y1, const Color& color);
	//void DrawLine(float x0, float y0, float x1, float y1, const Color& color);
	//void DrawLine(const Vector2f& v0, const Vector2f& v1, const Color& color);

	//void DrawTriangle(std::span<Vector2i> verticies, const Color& color);

	//void DrawVerticies(std::span<Vector2f> verticies, const Color& color);
	//void DrawVerticies(std::span<Vector3f> verticies, const Color& color);
	//void DrawVerticies(const std::vector<Vector2f>& verticies, const Color& color);
	//
	//void DrawCircle(int x, int y, int radius, const Color& color);
	//void DrawCircle(const Vector2f& position, float radius, const Color& color);

	static void SetWindowContext(Window* windowContext);
	static void StartRendering(const Camera* camera);
	static void DrawSprite(const SpriteRenderer* spriteRenderer);
	static void DrawCircle(const CircleRenderer* circleRenderer);
	static void DrawLine(const LineRenderer* lineRenderer);
	static void DrawPixel(const PixelRenderer* pixelRenderer);
	static void DrawMesh(const Mesh* mesh);
};