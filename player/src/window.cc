#include "window.h"

#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>

#include "format.h"
#include "model.h"

Xe::Window::Window(QWidget* parent) : QWidget(parent) {
  layout = new QVBoxLayout();
  this->setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);

  _media = new Media(this);

  _view = new Xe::View(_media->model(), this);
  _controls = new Xe::Controls(_media, this);

  layout->addWidget(_view);
  layout->addWidget(_controls);

  QObject::connect(_media, &Media::playingChanged, this, &Window::setTitle);
}

void Xe::Window::setTitle(const QString& value) {
  if (value.isEmpty())
    setWindowTitle("XeAP");
  else
    this->setWindowTitle(value + " - " + QCoreApplication::applicationName());
}
