#pragma once
#include "Window.h"

class WindowsWindow : public Window
{
private:
	HINSTANCE m_HInstance;
	WNDCLASS m_WindowClass;
	HWND m_HWindow;
	HDC m_HDeviceContext;
	HDC m_HBitmapDC;

	HBITMAP m_HBitmap;
	HGDIOBJ m_HPreviousObj;

	BITMAPINFO m_BitmapInfo;

	std::vector<COLORREF> m_PixelBuffer;

public:
	WindowsWindow(int width, int height);

	void Update() override;
	void Clear() override;
	void ClearColor(const Color& color) override { }
	void Draw() override { };

	void SetPixel(int x, int y, const Color& color) override;
	 
	void SetTitle(const wchar_t* title) override;

	const Color& GetColor(int x, int y) override { return Color(); };
	const Color& GetColor(float x, float y) override { return Color(); };
	const Color& GetColor(const Vector2f& v) override{ return Color(); };

	const wchar_t* GetTitle() const override;

	~WindowsWindow() override;
};