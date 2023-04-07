#pragma once
#include "Keys.h"
#include "MouseButtons.h"

class Input
{
public:
	static bool IsKeyPressed(Key key);
	static bool IsKeyReleased(Key key);

	static bool IsMouseButtonPressed(MouseButton button);
	static bool IsMouseButtonReleased(MouseButton button);
};