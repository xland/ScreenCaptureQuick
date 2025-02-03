#include <Windows.h>
#include "ProviderImgScreen.h"

ProviderImgScreen::ProviderImgScreen() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

ProviderImgScreen::~ProviderImgScreen()
{
}

void ProviderImgScreen::printScreen(const int& x, const int& y, const int& w, const int& h)
{
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    DeleteObject(SelectObject(hDC, hBitmap));
    BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x, y, SRCCOPY);
    img = QImage(w, h, QImage::Format_ARGB32);
    BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), (long)w, 0 - (long)h, 1, 32, BI_RGB, (DWORD)w * 4 * h, 0, 0, 0, 0 };
    GetDIBits(hDC, hBitmap, 0, h, img.bits(), &bmi, DIB_RGB_COLORS);
    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
}

QImage ProviderImgScreen::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    if (img.isNull()) {
        auto x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        auto y = GetSystemMetrics(SM_YVIRTUALSCREEN);
        auto w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        auto h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
        printScreen(x, y, w, h);
    }
    return img;
}
