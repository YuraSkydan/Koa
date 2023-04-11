#pragma once
#include "Keys.h"
#include "MouseButtons.h"
#include "../Math/Vector2.h"

class Input
{
public:
	static bool IsKeyPressed(Key key);
	static bool IsKeyReleased(Key key);

	static bool IsMouseButtonPressed(MouseButton button);
	static bool IsMouseButtonReleased(MouseButton button);

	static Vector2f GetMousePosition();
};