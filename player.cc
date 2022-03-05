#include "mainwidget.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("xe-player");
    QCoreApplication::setOrganizationName("xio");
    QCoreApplication::setOrganizationDomain("xio.com");

    QApplication app(argc, argv);
    Xe::MainWidget xe_widget;
    xe_widget.show();
    return app.exec();
}
