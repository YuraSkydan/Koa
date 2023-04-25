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
	void ClearColor(Color color) override { }
	void Draw() override { };

	void SetPixel(int x, int y, Color color) override;
	 
	void SetTitle(const wchar_t* title) override;

	Pixel GetPixel(int x, int y) override { return Pixel(); };
	Pixel GetPixel(float x, float y) override { return Pixel(); };
	Pixel GetPixel(const Vector2f& v) override{ return Pixel(); };

	const wchar_t* GetTitle() const override
	{
		return nullptr;
	};

	~WindowsWindow() override;
};