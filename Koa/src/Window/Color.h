#pragma once
#include <Windows.h>
#include <vector>
#include "../Math/Vector3.h"

//Black
//(0, 0, 0), Color::Black, Shade::None
//
//DarkBlue
//( 0, 55, 218), Color::DarkBlue, Shade::None;
//( 3, 54, 188), Color::DarkBlue, Shade::Dark;
//(10, 36, 126), Color::DarkBlue, Shade::Medium;
//( 8, 28,  56), Color::DarkBlue, Shade::Light;
// 
//DarkGreen
//(19, 161, 14), Color::DarkGreen, Shade::None;
//(17, 140, 14), Color::DarkGreen, Shade::Dark;
//(16,  94, 14), Color::DarkGreen, Shade::Medium;
//(14,  70, 13), Color::DarkGreen, Shade::Light; 
//
//DarkCyan
//(58, 150, 221), Color::DarkCyan, Shade::None; 
//(51, 130, 191), Color::DarkCyan, Shade::Dark;
//(37,  88, 128), Color::DarkCyan, Shade::Medium;
//(21,  13,  57), Color::DarkCyan, Shade::Light; 
//    
//DarkRed
//(199, 72, 75), Color::DarkRed, Shade::None;
//(170, 16, 31), Color::DarkRed, Shade::Dark;
//(114, 14, 19), Color::DarkRed, Shade::Medium;
//( 51, 13, 16), Color::DarkRed, Shade::Light;
// 
//DarkMagenta
//(136, 23, 152), Color::DarkMagenta, Shade::None; 
//(118, 21, 131), Color::DarkMagenta, Shade::Dark;
//( 60, 16,  89), Color::DarkMagenta, Shade::Medium; 
//( 60, 14,  42), Color::DarkMagenta, SHade::Light;  
// 
//DarkYellow
//(193, 156,  0), Color::DarkYellow, Shade::None;
//(168, 135,  0), Color::DarkYellow, Shade::Dark;
//( 83,  91, 10), Color::DarkYellow, Shade::Medium;
//( 50,  13, 11), Color::DarkYellow, Shade::Light;
//
//DarkGray
//(204, 204, 204), Color::DarkGray, Shade::None;
//(177, 177, 204), Color::DarkGray, Shade::Dark;
//( 87,  87, 118), Color::DarkGray, Shade::Medium;
//( 52,  52,  52), Color::DarkGray, Shade::Light; 
// 
//Gray
//(118, 118, 118), Color::Gray, Shade::None;
//(102, 102, 118), Color::Gray, Shade::Dark;
//( 52,  52,  70), Color::Gray, Shade::Medium;  
//( 70,  52,  34), Color::Gray, Shade::Light;
//   
//Blue
//(59, 120, 255), Color::Blue, Shade::None;
//(52, 104, 220), Color::Blue, Shade::Dark; 
//(29,  71, 146), Color::Blue, Shade::Medium; 
//(21,  53, 107), Color::Blue, Shade::Light;
//  
//Green
//(22, 198, 12), Color::Green, Shade::None;
//(20, 171, 13), Color::Green, Shade::Dark;
//(16, 115, 13), Color::Green, Shade::Medium;  
//(14, 84,  13), Color::Green, Shade::Light;
// 
//Cyan
//(97, 214, 214), Color::Cyan, Shade::None;
//(85, 185, 214), Color::Cyan, Shade::Dark;
//(44, 124,  91), Color::Cyan, Shade::Medium;   
//(29,  54,  54), Color::Cyan, Shade::Light;
// 
//Red
//(231, 72, 86), Color::Red, Shade::None;
//(199, 63, 86), Color::Red, Shade::Dark;
//( 97, 24, 40), Color::Red, Shade::Medium;
//( 59, 24, 27), Color::Red, Shade::Light;
//
//Magenta 
//(180,  0, 158), Color::Magenta, Shade::None;
//(156,  0, 158), Color::Magenta, Shade::Dark;
//(105, 10,  69), Color::Magenta, Shade::Medium;
//( 48, 10,  69), Color::Magenta, Shade::Light;
// 
//Yellow
//(249, 241, 165), Color::Yellow, Shade::None;  
//(215, 207, 143), Color::Yellow, Shade::Dark;
//(144, 139,  96), Color::Yellow, Shade::Medium;
//(104,  61,  44), Color::Yellow, Shade::Light;
//
//White
//(242, 242, 242), Color::White, Shade::None;
//(208, 208, 208), Color::White, Shade::Dark;
//(139, 139, 175), Color::White, Shade::Medium;
//( 61,  61,  61), Color::White, Shade::Light;

//enum class Color
//{
//	Black       = 0,
//	DarkBlue    = FOREGROUND_BLUE,
//	DarkGreen   = FOREGROUND_GREEN,
//	DarkRed     = FOREGROUND_RED,
//	DarkCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE,
//	DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
//	DarkYellow  = FOREGROUND_RED | FOREGROUND_GREEN,
//	DarkGray    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
//	Gray        = FOREGROUND_INTENSITY,
//	Blue        = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
//	Green       = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
//	Cyan        = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
//	Red         = FOREGROUND_INTENSITY | FOREGROUND_RED,
//	Magenta     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
//	Yellow      = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
//	White       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
//	Count
//};

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

	ColorType m_ColorValue = White;
	Shade m_Shade = Shade::None;

public:
	Color() = default;
	Color(ColorType colorValue, Shade shade = Shade::None);
	Color(Shade shade);
	Color(const Vector3ui& color);
	
	void SetColorValue(ColorType color);
	void SetColorRGB(const Vector3ui& color);

	void SetShade(Shade shade);

	ColorType GetColorValue() const;
	Shade GetShade() const;
};