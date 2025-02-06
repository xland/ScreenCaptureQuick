#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qquickitem.h>
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
    window->setScreen(QGuiApplication::primaryScreen());

    auto dpr = window->devicePixelRatio();
    if (window) {
        window->setFlags(window->flags() | Qt::FramelessWindowHint);
        auto hwnd = (HWND)window->winId();
        auto x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        auto y = GetSystemMetrics(SM_YVIRTUALSCREEN);
        auto w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        auto h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
        SetWindowPos(hwnd,  HWND_TOP,   
            x, y,       
            w, h,       
            SWP_NOZORDER );
    }
    return app.exec();
}
