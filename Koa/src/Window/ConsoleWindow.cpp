#include <cstring>
#include <algorithm>

#include "ConsoleWindow.h"
#include "../Math/VectorOperations.h"

void ConsoleWindow::ResizeBuffers()
{
	m_BufferSize = int(m_ConsoleBufferSize.X) * int(m_ConsoleBufferSize.Y);
	m_Buffers[0].resize(m_BufferSize);
	m_Buffers[1].resize(m_BufferSize);

	memset(m_Buffers[0].data(), 0, m_Buffers[0].size() * sizeof(CHAR_INFO));
	memset(m_Buffers[1].data(), 0, m_Buffers[1].size() * sizeof(CHAR_INFO));
}

void ConsoleWindow::DrawPart(const COORD& writePosition, SMALL_RECT ConsoleWindowSize)
{
	WriteConsoleOutput(m_Console, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, writePosition, &ConsoleWindowSize);
}

WCHAR ConsoleWindow::GetShadeCharacter(Color::Shade shade)
{
	switch (shade)
	{
	case Color::Shade::None:
		return 9608;

	case Color::Shade::Dark:
		return 9619;

	case Color::Shade::Medium:
		return 9618;

	case Color::Shade::Light:
		return 9617;

	case Color::Shade::Transparent:
		return  ' ';
	}
}

ConsoleWindow::ConsoleWindow(int width, int height)
	: Window(width, height)
{
#if CUSTOM_CONSOLE_BUFFER
	m_ConsoleBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_ConsoleBuffer);
#endif

	m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
	m_ConsoleWindow = GetConsoleWindow();
	m_Style = GetWindowLong(m_ConsoleWindow, GWL_STYLE);

	GetConsoleCursorInfo(m_Console, &m_ConsoleCursor);
	GetConsoleScreenBufferInfo(m_Console, &m_ConsoleBufferInfo);

	m_ConsoleWindowSize = m_ConsoleBufferInfo.srWindow;
	m_ConsoleBufferSize = m_ConsoleBufferInfo.dwSize;
	m_WritePosition = { 0, 0 };

	m_CurrentBufferIndex = 0;
	m_NextBufferIndex = 1;

	DWORD prev_mode;
	GetConsoleMode(m_Console, &prev_mode);
	SetConsoleMode(m_Console, ENABLE_EXTENDED_FLAGS |
		(prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	SetConsoleActiveScreenBuffer(m_Console);

	ResizeBuffers();

	SetConsoleBufferSize({ short(width + 1), short(height + 1) });
	SetConsoleWindowSize({ short(width), short(height) });
}

void ConsoleWindow::Update()
{
	SwapBuffers();
	Draw();
}

void ConsoleWindow::Clear()
{
	memset(m_Buffers[m_CurrentBufferIndex].data(), 0, m_Buffers[m_CurrentBufferIndex].size() * sizeof(CHAR_INFO));
}

void ConsoleWindow::ClearColor(Color color)
{
	for (auto it = m_Buffers[m_NextBufferIndex].begin(), end = m_Buffers[m_NextBufferIndex].end(); it != end; ++it)
	{
		it->Char.UnicodeChar = GetShadeCharacter(Color::Shade::None);
		it->Attributes = WORD(color.GetConsoleColor());
	}
}

void ConsoleWindow::SwapBuffers()
{
	size_t temp = m_CurrentBufferIndex;
	m_CurrentBufferIndex = m_NextBufferIndex;
	m_NextBufferIndex = temp;
}

void ConsoleWindow::Draw()
{
#if MULTITHREADED_X_DRAW
	size_t threadsAmount = std::thread::hardware_concurrency();
	std::vector<std::thread> drawThreads;

	float writePositionStep = m_ConsoleBufferSize.X / float(threadsAmount);
	float ConsoleWindowSizeStep = m_ConsoleConsoleWindowSize.Right / float(threadsAmount);

	for (size_t i = 0; i < threadsAmount; i++)
	{
		COORD writePosition = m_WritePosition;
		SMALL_RECT ConsoleWindowSize = m_ConsoleConsoleWindowSize;

		writePosition.X = writePositionStep * i;

		ConsoleWindowSize.Left = ConsoleWindowSizeStep * i;
		ConsoleWindowSize.Right = ConsoleWindowSizeStep * (i + 1);

		//DrawPa5rt(writePosition, ConsoleWindowSize);

		drawThreads.push_back(std::thread(&ConsoleWindow::DrawPart, this, writePosition, ConsoleWindowSize));
	}

	for (size_t i = 0; i < drawThreads.size(); i++)
	{
		drawThreads[i].join();
	}
#elif MULTITHREADED_Y_DRAW
	size_t threadsAmount = std::thread::hardware_concurrency();
	std::vector<std::thread> drawThreads;

	float writePositionStep = m_ConsoleBufferSize.Y / float(threadsAmount);
	float ConsoleWindowSizeStep = m_ConsoleConsoleWindowSize.Bottom / float(threadsAmount);

	for (size_t i = 0; i < threadsAmount; i++)
	{
		COORD writePosition = m_WritePosition;
		SMALL_RECT ConsoleWindowSize = m_ConsoleConsoleWindowSize;

		writePosition.Y = writePositionStep * i;

		ConsoleWindowSize.Top = ConsoleWindowSizeStep * i;
		ConsoleWindowSize.Bottom = ConsoleWindowSizeStep * (i + 1);

		//DrawPa5rt(writePosition, ConsoleWindowSize);

		drawThreads.push_back(std::thread(&ConsoleWindow::DrawPart, this, writePosition, ConsoleWindowSize));
	}

	for (size_t i = 0; i < drawThreads.size(); i++)
	{
		drawThreads[i].join();
	}
#elif CUSTOM_CONSOLE_BUFFER
	WriteConsoleOutput(m_ConsoleBuffer, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, m_WritePosition, &m_ConsoleConsoleWindowSize);
#else
	WriteConsoleOutput(m_Console, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, m_WritePosition, &m_ConsoleWindowSize);
#endif
}

void ConsoleWindow::SetPixel(int x, int y, Color color)
{
	if (x < 0 || y < 0 || x >= m_ConsoleBufferSize.X || y >= m_ConsoleBufferSize.Y)
	{
		return;
	}

	unsigned int position = y * m_ConsoleBufferSize.X + x;

	m_Buffers[m_NextBufferIndex][position].Char.UnicodeChar = GetShadeCharacter(color.GetConsoleColorShade());
	m_Buffers[m_NextBufferIndex][position].Attributes = WORD(color.GetConsoleColor());
}

void ConsoleWindow::EnableCursor()
{
	m_ConsoleCursor.bVisible = true;
	SetConsoleCursorInfo(m_Console, &m_ConsoleCursor);
}

void ConsoleWindow::DisableCursor()
{
	m_ConsoleCursor.bVisible = false;
	SetConsoleCursorInfo(m_Console, &m_ConsoleCursor);
}

void ConsoleWindow::EnableScrollBar()
{
	DWORD consoleMode;
	GetConsoleMode(m_Console, &consoleMode);
	//consoleMode &= SCROLLBAR;
}

void ConsoleWindow::DisableScrollBar()
{

}

void ConsoleWindow::EnableResize()
{
	m_Style &= ~WS_THICKFRAME;
	SetWindowLong(m_ConsoleWindow, GWL_STYLE, m_Style);
}

void ConsoleWindow::DisableResize()
{
	m_Style &= WS_THICKFRAME;
	SetWindowLong(m_ConsoleWindow, GWL_STYLE, m_Style);
}

void ConsoleWindow::SetConsoleWindowSize(const SMALL_RECT& size)
{
	m_ConsoleWindowSize = size;

#if CUSTOM_CONSOLE_BUFFER
	SetConsoleConsoleWindowInfo(m_ConsoleBuffer, TRUE, &m_ConsoleConsoleWindowSize);
#else
	SetConsoleWindowInfo(m_Console, TRUE, &m_ConsoleWindowSize);
#endif
}

void ConsoleWindow::SetConsoleBufferSize(const COORD& size)
{
	m_ConsoleBufferSize = size;

#if CUSTOM_CONSOLE_BUFFER
	SetConsoleScreenBufferSize(m_ConsoleBuffer, m_ConsoleBufferSize);
#else
	SetConsoleScreenBufferSize(m_Console, m_ConsoleBufferSize);
#endif

	ResizeBuffers();
}

void ConsoleWindow::SetWritePosition(const COORD& position)
{
	m_WritePosition = position;
}

void ConsoleWindow::SetFont(const wchar_t* fontName, short fontWidth, short fontHeight, unsigned int fontWeight, unsigned int fontFamily)
{
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = fontWidth;
	fontInfo.dwFontSize.Y = fontHeight;
	fontInfo.FontFamily = fontFamily;
	fontInfo.FontWeight = fontWeight;

	std::wcscpy(fontInfo.FaceName, fontName);

#if CUSTOM_CONSOLE_BUFFER
	SetCurrentConsoleFontEx(m_ConsoleBuffer, FALSE, &fontInfo);
#else
	SetCurrentConsoleFontEx(m_Console, FALSE, &fontInfo);
#endif
}

void ConsoleWindow::SetTitle(const wchar_t* title)
{
	SetConsoleTitleW(title);
}

Pixel ConsoleWindow::GetPixel(int x, int y)
{
	return Pixel();
}

const SMALL_RECT& ConsoleWindow::GetConsoleWindowSize() const
{
	return m_ConsoleWindowSize;
}

const COORD& ConsoleWindow::GetConsoleBufferSize() const
{
	return m_ConsoleBufferSize;
}

const COORD& ConsoleWindow::GetWritePosition() const
{
	return m_WritePosition;
}

const wchar_t* ConsoleWindow::GetTitle() const
{
	static wchar_t title[MAX_PATH];
	GetConsoleTitleW(title, MAX_PATH);
	return title;
}