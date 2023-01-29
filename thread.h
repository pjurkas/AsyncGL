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

        void start();
        void stop();

    protected:

        void run() override;

    private:

        bool m_running;
    };
}
