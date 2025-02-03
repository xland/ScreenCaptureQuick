#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QImage>

class ProviderImgScreen  : public QQuickImageProvider
{
	Q_OBJECT

public:
	ProviderImgScreen();
	~ProviderImgScreen();
	QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
private:
	void printScreen(const int& x, const int& y, const int& w, const int& h);
	QImage img;
};
