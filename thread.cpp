
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

    void Thread::run()
    {
        auto window = dynamic_cast<Window *>(parent());

        window->initialize();

        auto counter = 0;
        auto a = std::chrono::system_clock::now();
        while (m_running)
        {
            window->render();
            ++counter;
            
            if (counter % 100 == 0)
            {
                auto b = std::chrono::system_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count();
                double fps = 1000.0 * counter / duration;
                std::cerr << "FPS: " << fps << std::endl;
            }
        }
    }

    void Thread::start()
    {
        m_running = true;
        QThread::start();
    }

    void Thread::stop()
    {
        m_running = false;
        QThread::wait();
    }
}
