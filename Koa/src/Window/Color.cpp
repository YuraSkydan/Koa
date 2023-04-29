#include "Color.h"
#include "../Math/VectorOperations.h"
#include "../Core/Engine.h"

std::vector<std::pair<Vector3ui, Color>> Color::s_RGBColors =
  { { Vector3ui(0, 0, 0), { Color::Black, Shade::None } },

  { Vector3ui( 0, 55, 218), { Color::DarkBlue, Shade::None   } },
  {	Vector3ui( 2, 51, 197), { Color::DarkBlue, Shade::Dark   } },
  {	Vector3ui( 9, 30, 109), { Color::DarkBlue, Shade::Medium } },
  { Vector3ui(10, 21,  69), { Color::DarkBlue, Shade::Light  } },
 
  { Vector3ui(19, 161, 14), { Color::DarkGreen, Shade::None   } },
  { Vector3ui(17, 148, 14), { Color::DarkGreen, Shade::Dark   } },
  { Vector3ui(14,  77, 13), { Color::DarkGreen, Shade::Medium } },
  { Vector3ui(14,  40, 13), { Color::DarkGreen, Shade::Light  } },

  { Vector3ui(58, 150, 221), { Color::DarkCyan, Shade::None   } },
  { Vector3ui(51, 130, 191), { Color::DarkCyan, Shade::Dark   } },
  { Vector3ui(29,  66, 93), { Color::DarkCyan, Shade::Medium } },
  { Vector3ui(22,  41, 69), { Color::DarkCyan, Shade::Light  } },

  { Vector3ui(199, 15, 31), { Color::DarkRed, Shade::None   } },
  { Vector3ui(179, 16, 29), { Color::DarkRed, Shade::Dark   } },
  { Vector3ui(89, 14, 20), { Color::DarkRed, Shade::Medium } },
  { Vector3ui(55, 12, 16),  { Color::DarkRed, Shade::Light  } },

  { Vector3ui(136, 23, 152), { Color::DarkMagenta, Shade::None   } },
  { Vector3ui(122, 21, 140), { Color::DarkMagenta, Shade::Dark   } },
  { Vector3ui(64,  16,  78), { Color::DarkMagenta, Shade::Medium } },
  { Vector3ui(41,  14,  48), { Color::DarkMagenta, Shade::Light  } },

  { Vector3ui(193, 156,  0), { Color::DarkYellow, Shade::None   } },
  { Vector3ui(176, 146,  0), { Color::DarkYellow, Shade::Dark   } },
  { Vector3ui( 90,  75, 8), { Color::DarkYellow, Shade::Medium } },
  { Vector3ui( 56,  39, 10), { Color::DarkYellow, Shade::Light  } },

  { Vector3ui(204, 204, 204), { Color::DarkGray, Shade::None   } },
  { Vector3ui(186, 186, 288), { Color::DarkGray, Shade::Dark   } },
  { Vector3ui(94,  99, 103), { Color::DarkGray, Shade::Medium } },
  { Vector3ui(57,  51,  61), { Color::DarkGray, Shade::Light  } },

  { Vector3ui(118, 118, 118), { Color::Gray, Shade::None   } },
  { Vector3ui(105, 108, 108), { Color::Gray, Shade::Dark   } },
  { Vector3ui(56,  58,  61), { Color::Gray, Shade::Medium } },
  { Vector3ui(35,  35,  40), { Color::Gray, Shade::Light  } },

  { Vector3ui(59, 120, 255), { Color::Blue, Shade::None   } },
  { Vector3ui(54, 111, 234), { Color::Blue, Shade::Dark   } },
  { Vector3ui(30,  58, 127), { Color::Blue, Shade::Medium } },
  { Vector3ui(22,  33,  75), { Color::Blue, Shade::Light  } },

  { Vector3ui(22, 198, 12), { Color::Green, Shade::None   } },
  { Vector3ui(20, 182, 13), { Color::Green, Shade::Dark   } },
  { Vector3ui(16, 97, 13), { Color::Green, Shade::Medium } },
  { Vector3ui(14, 47, 13), { Color::Green, Shade::Light  } },

  { Vector3ui(97, 214, 214), { Color::Cyan, Shade::None   } },
  { Vector3ui(89, 197, 297), { Color::Cyan, Shade::Dark   } },
  { Vector3ui(47, 103, 108), { Color::Cyan, Shade::Medium } },
  { Vector3ui(31,  52,  64), { Color::Cyan, Shade::Light  } },

  { Vector3ui(231, 72, 86), { Color::Red, Shade::None   } },
  { Vector3ui(210, 67, 79), { Color::Red, Shade::Dark   } },
  { Vector3ui(105, 38, 46), { Color::Red, Shade::Medium } },
  { Vector3ui(66, 23, 30), { Color::Red, Shade::Light  } },

  { Vector3ui(180,  0, 158), { Color::Magenta, Shade::None   } },
  { Vector3ui(164,  1, 142), { Color::Magenta, Shade::Dark   } },
  { Vector3ui( 83,  9,  81), { Color::Magenta, Shade::Medium } },
  { Vector3ui( 52, 10,  50), { Color::Magenta, Shade::Light  } },

  { Vector3ui(249, 241, 165), { Color::Yellow, Shade::None   } },
  { Vector3ui(226, 221, 152), { Color::Yellow, Shade::Dark   } },
  { Vector3ui(113, 113,  83), { Color::Yellow, Shade::Medium } },
  { Vector3ui(65,  64,   53), { Color::Yellow, Shade::Light  } },

  { Vector3ui(242, 242, 242), { Color::White, Shade::None   } },
  { Vector3ui(219, 222, 222), { Color::White, Shade::Dark   } },
  { Vector3ui(108, 117, 118), { Color::White, Shade::Medium } },
  { Vector3ui(66,  62,  72), { Color::White, Shade::Light  } }
};


Color::Color(ColorType colorValue, Shade shade)
	: m_ConsoleColor(colorValue), m_ConsoleColorShade(shade)
{ }

Color::Color(Shade shade)
	: m_ConsoleColorShade(shade)
{ }

Color::Color(const Vector3ui& color)
{
	SetColorRGB(color);
}

void Color::SetConsoleColor(ColorType color)
{
	m_ConsoleColor = color;
}

void Color::SetColorRGB(const Vector3ui& color)
{
	m_RGBColor = color;

	if (Engine::Get().GetWindowContext() == Engine::WindowContext::Console)
	{
		auto closestColor = s_RGBColors.begin();
		float closestDistance = FLT_MAX;

		for (auto it = s_RGBColors.begin(), end = s_RGBColors.end(); it != end; ++it)
		{
			int dr = int(m_RGBColor.x) - int(it->first.x);
			int dg = int(m_RGBColor.y) - int(it->first.y);
			int db = int(m_RGBColor.z) - int(it->first.z);
			float distance = sqrt(dr * dr + dg * dg + db * db);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestColor = it;
			}
		}

		m_ConsoleColor = closestColor->second.GetConsoleColor();
		m_ConsoleColorShade = closestColor->second.GetConsoleColorShade();
	}
}

void Color::SetConsoleColorShade(Shade shade)
{
	m_ConsoleColorShade = shade;
}

ColorType Color::GetConsoleColor() const
{
	return m_ConsoleColor;
}

const Vector3ui& Color::GetRGBColor() const
{
	return m_RGBColor;
}

Color::Shade Color::GetConsoleColorShade() const
{
	return m_ConsoleColorShade;
}