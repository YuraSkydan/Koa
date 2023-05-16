#pragma once
#include <vector>
#include "../Math/Vector2.h"

class Entity;
class PixelPhysics;

class PixelPhysicsGrid
{
private:
	Vector2i m_DownLeftBorder;
	Vector2i m_UpRightBorder;
	int m_Width;
	int m_Height;
	std::vector<PixelPhysics*> m_PhysicsPixels;
private:
	void ResizeGrid();

public:
	PixelPhysicsGrid(const Vector2i& downLeftBorder, const Vector2i& upRightBorder);
	void Simulate();

	void AddPhysicsPixel(PixelPhysics* pixelPhysics);

	PixelPhysics* GetPixelPhysics(int x, int y);
	const PixelPhysics* GetPixelPhysics(int x, int y) const;

	void SetDownLeftBorder(const Vector2i& downLeft);
	void SetUpRightBorder(const Vector2i& upRightBorder);

	const Vector2i& GetDownLeftBorder() const;
	const Vector2i& GetUpRightBorder() const;
};