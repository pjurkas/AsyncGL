
#include "thread.h"
#include "window.h"

#include <chrono>
#include <iostream>

namespace asyncgl
{
    Thread::Thread(Window *parent)
        : QThread(parent)
        , m_running(false)
    {}

    void Thread::start()
    {
        if (!m_running)
        {
            m_running = true;
            QThread::start();
        }
    }

    void Thread::stop()
    {
        if (m_running)
        {
            m_running = false;
            QThread::wait();
        }
    }

    void Thread::run()
    {
        auto window = dynamic_cast<Window *>(parent());

        window->initialize();

        auto counter = 0;
        auto max_fps = 0.0;
        auto a = std::chrono::system_clock::now();
        while (m_running)
        {
            window->render();
            ++counter;

            auto b = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count();
            if (duration > 1000)
            {
                double fps = 1000.0 * counter / duration;
                printf("FPS: %4.2f\n", fps);
                counter = 0;
                a = b;
            }
        }
    }
}
