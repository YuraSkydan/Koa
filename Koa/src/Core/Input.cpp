#include "Input.h"

bool Input::IsKeyPressed(Key key)
{
	return GetAsyncKeyState(static_cast<int>(key));
}

bool Input::IsKeyReleased(Key key)
{
	return GetAsyncKeyState(static_cast<int>(key)) == 0;
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
	return GetAsyncKeyState(static_cast<int>(button));
}

bool Input::IsMouseButtonReleased(MouseButton button)
{
	return GetAsyncKeyState(static_cast<int>(button)) == 0;
}