#pragma once
#include <Windows.h>
#include <vector>
#include <thread>

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Core/Defines.h"
#include "Window.h"
#include "Pixel.h"

class ConsoleWindow : public Window
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
	ConsoleWindow(int width, int height);

	void Update() override;

	void Clear() override;
	void ClearColor(Color color) override;
	void Draw() override;
	void SwapBuffers();

	void SetPixel(int x, int y, Color color) override;
	
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
	void SetTitle(const wchar_t* title) override;

	Pixel GetPixel(int x, int y) override;
	Pixel GetPixel(float x, float y) override { return Pixel(); };
	Pixel GetPixel(const Vector2f& v) override { return Pixel(); };

	const SMALL_RECT& GetConsoleWindowSize() const;
	const COORD& GetConsoleBufferSize() const;
	const COORD& GetWritePosition() const;
	const wchar_t* GetTitle() const override;
};