#include "xe.h"
#include "mainwidget.h"

#include <QCoreApplication>
#include <QApplication>


int Xe::run(int argc, char* argv[]) {

    QCoreApplication::setApplicationName("xe");
    QCoreApplication::setOrganizationName("xio");
    QCoreApplication::setOrganizationDomain("xe.xio.org");

    QApplication app(argc, argv);
    Xe::MainWidget xe_widget;
    xe_widget.show();
    return app.exec();
}