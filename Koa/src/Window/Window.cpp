#include <cstring>
#include <algorithm>

#include "Window.h"
#include "../Math/VectorOperations.h"

void Window::ResizeBuffers()
{
	m_BufferSize = int(m_ConsoleBufferSize.X) * int(m_ConsoleBufferSize.Y);
	m_Buffers[0].resize(m_BufferSize);
	m_Buffers[1].resize(m_BufferSize);

	memset(m_Buffers[0].data(), 0, m_Buffers[0].size() * sizeof(CHAR_INFO));
	memset(m_Buffers[1].data(), 0, m_Buffers[1].size() * sizeof(CHAR_INFO));
}

void Window::DrawPart(const COORD& writePosition, SMALL_RECT windowSize)
{
	WriteConsoleOutput(m_Console, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, writePosition, &windowSize);
}

WCHAR Window::GetShadeCharacter(Color::Shade shade)
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

Window::Window()
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
}

Window::Window(short width, short height)
	: Window()
{
	SetConsoleBufferSize({ short(width + 1), short(height + 1) });
	SetConsoleWindowSize({ width, height });
}

void Window::Update()
{
	SwapBuffers();
	Draw();
}

void Window::Clear()
{
	memset(m_Buffers[m_CurrentBufferIndex].data(), 0, m_Buffers[m_CurrentBufferIndex].size() * sizeof(CHAR_INFO));
}

void Window::ClearColor(Color color)
{
	for (auto it = m_Buffers[m_NextBufferIndex].begin(), end = m_Buffers[m_NextBufferIndex].end(); it != end; ++it)
	{
		it->Char.UnicodeChar = GetShadeCharacter(Color::Shade::None);
		it->Attributes = WORD(color.GetColorValue());
	}
}

void Window::SwapBuffers()
{
	size_t temp = m_CurrentBufferIndex;
	m_CurrentBufferIndex = m_NextBufferIndex;
	m_NextBufferIndex = temp;
}

void Window::Draw()
{
#if MULTITHREADED_X_DRAW
	size_t threadsAmount = std::thread::hardware_concurrency();
	std::vector<std::thread> drawThreads;

	float writePositionStep = m_ConsoleBufferSize.X / float(threadsAmount);
	float windowSizeStep = m_ConsoleWindowSize.Right / float(threadsAmount);

	for (size_t i = 0; i < threadsAmount; i++)
	{
		COORD writePosition = m_WritePosition;
		SMALL_RECT windowSize = m_ConsoleWindowSize;

		writePosition.X = writePositionStep * i;

		windowSize.Left = windowSizeStep * i;
		windowSize.Right = windowSizeStep * (i + 1);

		//DrawPa5rt(writePosition, windowSize);

		drawThreads.push_back(std::thread(&Window::DrawPart, this, writePosition, windowSize));
	}

	for (size_t i = 0; i < drawThreads.size(); i++)
	{
		drawThreads[i].join();
	}
#elif MULTITHREADED_Y_DRAW
	size_t threadsAmount = std::thread::hardware_concurrency();
	std::vector<std::thread> drawThreads;

	float writePositionStep = m_ConsoleBufferSize.Y / float(threadsAmount);
	float windowSizeStep = m_ConsoleWindowSize.Bottom / float(threadsAmount);

	for (size_t i = 0; i < threadsAmount; i++)
	{
		COORD writePosition = m_WritePosition;
		SMALL_RECT windowSize = m_ConsoleWindowSize;

		writePosition.Y = writePositionStep * i;

		windowSize.Top = windowSizeStep * i;
		windowSize.Bottom = windowSizeStep * (i + 1);

		//DrawPa5rt(writePosition, windowSize);

		drawThreads.push_back(std::thread(&Window::DrawPart, this, writePosition, windowSize));
	}

	for (size_t i = 0; i < drawThreads.size(); i++)
	{
		drawThreads[i].join();
	}
#elif CUSTOM_CONSOLE_BUFFER
	WriteConsoleOutput(m_ConsoleBuffer, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, m_WritePosition, &m_ConsoleWindowSize);
#else
	WriteConsoleOutput(m_Console, m_Buffers[m_CurrentBufferIndex].data(), m_ConsoleBufferSize, m_WritePosition, &m_ConsoleWindowSize);
#endif
}

void Window::SetPixel(int x, int y, Color color)
{
	if (x < 0 || y < 0 || x >= m_ConsoleBufferSize.X || y >= m_ConsoleBufferSize.Y)
	{
		return;
	}

	unsigned int position = y * m_ConsoleBufferSize.X + x;

	m_Buffers[m_NextBufferIndex][position].Char.UnicodeChar = GetShadeCharacter(color.GetShade());
	m_Buffers[m_NextBufferIndex][position].Attributes = WORD(color.GetColorValue());
}

void Window::SetPixel(float x, float y, Color color)
{
	int pixelX = (x * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	int pixelY = (-y * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	SetPixel(pixelX, pixelY, color);
}

void Window::Fill(int x, int y, Color color)
{
	if (x < 0 || y < 0 || x >= m_ConsoleBufferSize.X || y >= m_ConsoleBufferSize.Y)
	{
		return;
	}
	
	if (m_Buffers[m_NextBufferIndex][y * m_ConsoleBufferSize.X + x].Attributes == color.GetColorValue())
	{
		return;
	}
	
	SetPixel(x, y, color);

	Fill(x + 1, y, color);
	Fill(x, y + 1, color);
	Fill(x - 1, y, color);
	Fill(x, y - 1, color);
}

void Window::Fill(float x, float y, Color color)
{
	int centerX = (x * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	int centerY = (y * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	Fill(centerX, centerY, color);
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
	int pixelX0 = (x0 * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	int pixelY0 = (-y0 * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	int pixelX1 = (x1 * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
	int pixelY1 = (-y1 * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;

	DrawLine(pixelX0, pixelY0, pixelX1, pixelY1, color);
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
		int x = (vertex.x * m_ConsoleBufferSize.X / 2.0f) + m_ConsoleBufferSize.X / 2.0f;
		int y = (-vertex.y * m_ConsoleBufferSize.Y / 2.0f) + m_ConsoleBufferSize.Y / 2.0f;
	
		convertedVerticies.emplace_back(Vector2i(x, y));
	}

	DrawTriangle(convertedVerticies, color);
	
	//Vector2f center;
	//for (auto& vertex : verticies)
	//{
	//	center += vertex / 2.0f;
	//}

	//Fill(center.x, center.y, color);
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

	//Fill(center.x, center.y, color, shade);
}

void Window::EnableCursor()
{
	m_ConsoleCursor.bVisible = true;
	SetConsoleCursorInfo(m_Console, &m_ConsoleCursor);
}

void Window::DisableCursor()
{
	m_ConsoleCursor.bVisible = false;
	SetConsoleCursorInfo(m_Console, &m_ConsoleCursor);
}

void Window::EnableScrollBar()
{
	DWORD consoleMode;
	GetConsoleMode(m_Console, &consoleMode);
	//consoleMode &= SCROLLBAR;
}

void Window::DisableScrollBar()
{

}

void Window::EnableResize()
{
	m_Style &= ~WS_THICKFRAME;
	SetWindowLong(m_ConsoleWindow, GWL_STYLE, m_Style);
}

void Window::DisableResize()
{
	m_Style &= WS_THICKFRAME;
	SetWindowLong(m_ConsoleWindow, GWL_STYLE, m_Style);
}

void Window::SetConsoleWindowSize(const SMALL_RECT& size)
{
	m_ConsoleWindowSize = size;

#if CUSTOM_CONSOLE_BUFFER
	SetConsoleWindowInfo(m_ConsoleBuffer, TRUE, &m_ConsoleWindowSize);
#else
	SetConsoleWindowInfo(m_Console, TRUE, &m_ConsoleWindowSize);
#endif
}

void Window::SetConsoleBufferSize(const COORD& size)
{
	m_ConsoleBufferSize = size;

#if CUSTOM_CONSOLE_BUFFER
	SetConsoleScreenBufferSize(m_ConsoleBuffer, m_ConsoleBufferSize);
#else
	SetConsoleScreenBufferSize(m_Console, m_ConsoleBufferSize);
#endif

	ResizeBuffers();
}

void Window::SetWritePosition(const COORD& position)
{
	m_WritePosition = position;
}

void Window::SetFont(const wchar_t* fontName, short fontWidth, short fontHeight, unsigned int fontWeight, unsigned int fontFamily)
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

void Window::SetTitile(const wchar_t* title)
{
	SetConsoleTitleW(title);
}

Pixel Window::GetPixel(int x, int y)
{
	return Pixel();
}

const SMALL_RECT& Window::GetConsoleWindowSize() const
{
	return m_ConsoleWindowSize;
}

const COORD& Window::GetConsoleBufferSize() const
{
	return m_ConsoleBufferSize;
}

const COORD& Window::GetWritePosition() const
{
	return m_WritePosition;
}

const wchar_t* Window::GetTitle() const
{
	static wchar_t title[MAX_PATH];
	GetConsoleTitleW(title, MAX_PATH);
	return title;
}