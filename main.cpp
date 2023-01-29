#include "window.h"

#include <QGuiApplication>
#include <QImage>
#include <QOpenGLTexture>

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<QImage> images;
    for (auto i = 1; i < argc; ++i)
    {
        auto image = QImage(argv[i]).convertToFormat(QImage::Format_RGB888);
        std::cout << "Loaded " << argv[i] << " "
            << image.width() << "x" << image.height() << std::endl;
        images.push_back(std::move(image));
    }

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSwapInterval(0);

    asyncgl::Window window(std::move(images));
    window.setFormat(format);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
