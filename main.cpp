#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QQuickWindow>
#include <Windows.h>

#include "ProviderImgScreen.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto imgProvider = new ProviderImgScreen();
    engine.addImageProvider(QLatin1String("ProviderImgScreen"), imgProvider);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    if (window) {
        window->setFlags(window->flags() | Qt::FramelessWindowHint);
        auto hwnd = (HWND)window->winId();
        auto x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        auto y = GetSystemMetrics(SM_YVIRTUALSCREEN);
        auto w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        auto h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
        SetWindowPos(
            hwnd,               // 窗口句柄
            HWND_TOP,           // 保持窗口在顶部
            x, y,               // 新位置的 X 和 Y 坐标
            w, h,      // 新宽度和高度
            SWP_NOZORDER        // 保持窗口的 Z 顺序不变
        );
    }
    return app.exec();
}
