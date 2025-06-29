#include <QApplication>
#include "FramelessWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FramelessWindow w;
    w.resize(800, 600);
    w.show();
    return app.exec();
}
