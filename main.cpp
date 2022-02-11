#include "window.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSwapInterval(0);

    asyncgl::Window window;
    window.setFormat(format);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
