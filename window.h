#pragma once

#include "thread.h"

#include <vector>

#include <QWindow>
#include <QOpenGLFunctions>

namespace asyncgl
{
    class Window : public QWindow, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:

        explicit Window(QWindow *parent = nullptr);

        void initialize();
        void render();
        void draw();

    protected:

        bool eventFilter(QObject *obj, QEvent *event);

    private:

        Thread m_thread;
        QOpenGLContext *m_context;

        GLuint m_pbo;
        GLuint m_texture;

        int m_index;

        std::vector<unsigned char> m_frames[3];
    };
}
