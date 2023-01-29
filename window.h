#pragma once

#include "thread.h"

#include <vector>

#include <QWindow>
#include <QOpenGLFunctions>

namespace asyncgl
{
    struct Frame
    {
        inline Frame(size_t w, size_t h)
            : width(w)
            , height(h)
        {
            data.resize(3 * w * h);
        }

        size_t width;
        size_t height;
        std::vector<unsigned char> data;
    };

    class Window : public QWindow, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:

        explicit Window(std::vector<QImage>&& images);

        void initialize();
        void render();
        void draw();

    protected:

        void upload(void *data, size_t size);
        bool eventFilter(QObject *obj, QEvent *event);

    private:

        Thread m_thread;
        QOpenGLContext *m_context;

        GLuint m_pbo;
        GLuint m_texture;

        int m_index;

        std::vector<QImage> m_images;
    };
}
