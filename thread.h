#pragma once

#include <QThread>

namespace asyncgl
{
    class Window;

    class Thread : public QThread
    {
        Q_OBJECT

    public:

        explicit Thread(Window *parent = 0);

        void run() override;

        void start();
        void stop();

    private:

        bool m_running;
    };
}
