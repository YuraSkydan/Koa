#pragma once
#include <Windows.h>
#include <vector>
#include "../Math/Vector3.h"

using ColorType = uint8_t;

class Color
{
public:
	enum : ColorType
	{
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkRed = FOREGROUND_RED,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		DarkGray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Gray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		Magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Count
	};

	enum class Shade
	{
		None = 0,
		Dark,
		Medium,
		Light,
		Transparent,
		Count
	};

private:
	static std::vector<std::pair<Vector3ui, Color>> s_RGBColors;

	ColorType m_ConsoleColor = White;
	Shade m_ConsoleColorShade = Shade::None;

	Vector3ui m_RGBColor = Vector3ui(255);

public:
	Color() = default;
	Color(ColorType colorValue, Shade shade = Shade::None);
	Color(Shade shade);
	Color(const Vector3ui& color);
	
	void SetConsoleColor(ColorType color);
	void SetColorRGB(const Vector3ui& color);

	void SetConsoleColorShade(Shade shade);

	const Vector3ui& GetRGBColor() const;
	ColorType GetConsoleColor() const;
	Shade GetConsoleColorShade() const;
};