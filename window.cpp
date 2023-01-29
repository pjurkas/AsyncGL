#define GL_GLEXT_PROTOTYPES

#include "window.h"

#include <GL/gl.h>
#include <GL/glu.h>

namespace asyncgl
{
    Window::Window(std::vector<QImage>&& images)
        : QWindow()
        , m_thread(this)
        , m_context(nullptr)
        , m_index(0)
        , m_images(images)
    {
        setSurfaceType(QWindow::OpenGLSurface);
        installEventFilter(this);
    }

    void Window::initialize()
    {
        if (m_context)
            return;

        m_context = new QOpenGLContext();
        m_context->setFormat(requestedFormat());
        m_context->create();
        m_context->makeCurrent(this);

        initializeOpenGLFunctions();

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenBuffers(1, &m_pbo);

        // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);
        // auto& image = m_images[0];
        // upload(image.bits(), 3 * image.width() * image.height());
        // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    void Window::render()
    {
        if (!isExposed())
            return;

        m_context->makeCurrent(this);

        draw();

        m_context->swapBuffers(this);
    }

    void Window::draw()
    {
        glViewport(0, 0, width(), height());

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo);

        auto& image = m_images[m_index];

        upload(image.bits(), 3 * image.width() * image.height());

        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        glEnable(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0); glVertex2f(-1, -1);
        glTexCoord2f(1.0, 1.0); glVertex2f(+1, -1);
        glTexCoord2f(1.0, 0.0); glVertex2f(+1, +1);
        glTexCoord2f(0.0, 0.0); glVertex2f(-1, +1);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        m_index = (m_index + 1) % m_images.size();
    }

    void Window::upload(void *data, size_t size)
    {
        glBufferData(GL_PIXEL_UNPACK_BUFFER, size, 0, GL_STREAM_DRAW);
        void* mappedBuffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
        memcpy(mappedBuffer, data, size);
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    }

    bool Window::eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::Expose)
            m_thread.start();
        if (event->type() == QEvent::Close)
            m_thread.stop();
        return QObject::eventFilter(obj, event);
    }
}
