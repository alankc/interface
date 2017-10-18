#include "mainwindow.h"
#include <QApplication>

#include "controllermainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ControllerMainWindow::SetView(&w);

    w.show();
    return a.exec();
}
