#include "player.h"
#include "window.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication::setApplicationName("XeAP");
  QCoreApplication::setOrganizationName("xio");
  QCoreApplication::setOrganizationDomain("org.xio.xeap");

  QApplication app(argc, argv);
  Xe::Window window;
  window.show();
  return app.exec();
}
