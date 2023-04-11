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
private:
	HANDLE m_Console;

#if CUSTOM_CONSOLE_BUFFER
	HANDLE m_ConsoleBuffer;
#endif

	HWND m_ConsoleWindow;
	SMALL_RECT m_ConsoleWindowSize; 

	CONSOLE_SCREEN_BUFFER_INFO m_ConsoleBufferInfo;
	CONSOLE_CURSOR_INFO m_ConsoleCursor;

	COORD m_ConsoleBufferSize;
	COORD m_WritePosition;

	LONG m_Style;

	std::vector<CHAR_INFO> m_Buffers[2];
	size_t m_BufferSize;

	size_t m_CurrentBufferIndex;
	size_t m_NextBufferIndex;

private:
	void ResizeBuffers();
	void DrawPart(const COORD& writePosition, SMALL_RECT windowSize);
	WCHAR GetShadeCharacter(Color::Shade shade);

public: 
	Window();
	Window(short width, short height);

	void Update();

	void Clear();
	void ClearColor(Color color);
	void SwapBuffers();
	void Draw();

	void SetPixel(int x, int y, Color color);
	void SetPixel(float x, float y, Color color);
	void SetPixel(const Vector2f& v, Color color);

	void Fill(int x, int y, Color color);
	void Fill(float x, float y, Color color);
	void Fill(const Vector2f& center, Color color);

	void DrawLine(int x0, int y0, int x1, int y1, Color color);
	void DrawLine(float x0, float y0, float x1, float y1, Color color);
	void DrawLine(const Vector2f& v0, const Vector2f& v1, Color color);

	void DrawTriangle(Vector2i verticies[3], Color color);
	void DrawTriangle(std::vector<Vector2i> verticies, Color color);

	void DrawVerticies(std::vector<Vector2f> verticies, Color color);
	void DrawVerticies(const std::vector<Vector3f>& verticies, Color color);

	void DrawCircle(int x, int y, int radius, Color color);
	void DrawCircle(const Vector2f& position, float radius, Color color);

	void EnableCursor();
	void DisableCursor();

	void EnableScrollBar();
	void DisableScrollBar();

	void EnableResize();
	void DisableResize();

	void SetConsoleWindowSize(const SMALL_RECT& size);
	void SetConsoleBufferSize(const COORD& size);
	void SetWritePosition(const COORD& position);

	void SetFont(const wchar_t* fontName, short fontWidth, short fontHeight, unsigned int fontWeight = 0, unsigned int fontFamily = FF_DONTCARE);
	void SetTitile(const wchar_t* title);

	Pixel GetPixel(int x, int y);
	Pixel GetPixel(float x, float y);
	Pixel GetPixel(const Vector2f& v);

	const SMALL_RECT& GetConsoleWindowSize() const;
	const COORD& GetConsoleBufferSize() const;
	const COORD& GetWritePosition() const;
	const wchar_t* GetTitle() const;
};