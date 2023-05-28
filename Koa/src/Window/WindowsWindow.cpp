#include "WindowsWindow.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) 
	{
	case WM_PAINT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

WindowsWindow::WindowsWindow(int width, int height)
	: Window(width, height)
{
	m_HInstance = GetModuleHandle(NULL);

	m_WindowClass = { 0 };
	m_WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	m_WindowClass.lpfnWndProc = WindowProc;
	m_WindowClass.hInstance = m_HInstance;

	m_WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	m_WindowClass.cbClsExtra = 0;
	m_WindowClass.cbWndExtra = 0;

	m_WindowClass.lpszMenuName = nullptr;

	m_WindowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	m_WindowClass.lpszClassName = L"WindowsWindow";

	RegisterClass(&m_WindowClass);

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

	RECT windowRect = { 0, 0, m_Width, m_Height };
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	m_HWindow = CreateWindowEx(dwExStyle, m_WindowClass.lpszClassName, L"Window", dwStyle,
		0, 0, m_Width, m_Height, NULL, NULL, m_HInstance, this);

	ShowWindow(m_HWindow, SW_SHOWDEFAULT);
	UpdateWindow(m_HWindow);

	m_HDeviceContext = GetDC(m_HWindow);

	m_HBitmap = CreateCompatibleBitmap(m_HDeviceContext, m_Width, m_Height);
	m_HBitmapDC = CreateCompatibleDC(m_HDeviceContext);

	m_HPreviousObj = SelectObject(m_HBitmapDC, m_HBitmap);

	m_BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BitmapInfo.bmiHeader.biWidth = m_Width;
	m_BitmapInfo.bmiHeader.biHeight = -m_Height;
	m_BitmapInfo.bmiHeader.biPlanes = 1;
	m_BitmapInfo.bmiHeader.biBitCount = 32;
	m_BitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	m_PixelBuffer.resize(m_Width * m_Height);
}

void WindowsWindow::Update()
{
	SetDIBitsToDevice(m_HDeviceContext, 0, 0, m_Width, m_Height, 0, 0, 0, m_Height, m_PixelBuffer.data(), &m_BitmapInfo, DIB_RGB_COLORS);

	//BitBlt(m_HDeviceContext, 0, 0, m_Width, m_Height, m_HBitmapDC, 0, 0, SRCPAINT);

	MSG msg;
	BOOL bRet;
	if(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void WindowsWindow::Clear()
{
	memset(m_PixelBuffer.data(), 0, sizeof(COLORREF) * m_PixelBuffer.size());
}

void WindowsWindow::SetPixel(int x, int y, const Color& color) 
{
	if (x < 0 || y < 0 || x >= m_Width || y >= m_Height)
	{
		return;
	}

	unsigned int position = y * m_Width + x;

	Vector3ui rgb = color.GetRGBColor();
	//m_PixelBuffer[position] = RGB(rgb.x, rgb.y, rgb.z);
	m_PixelBuffer[position] = RGB(rgb.z, rgb.y, rgb.x);
}

void WindowsWindow::SetTitle(const wchar_t* title)
{
	SetWindowText(m_HWindow, title);
}



const wchar_t* WindowsWindow::GetTitle() const
{
	//GetWindowText(m_HWindow);
	return nullptr;
}

WindowsWindow::~WindowsWindow() 
{ }