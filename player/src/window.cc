#include "window.h"
#include "format.h"
#include "model.h"

#include <QDir>
#include <QDirIterator>

Xe::Window::Window(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout();
  this->setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);

  _media = new Media(this);

  _view = new Xe::View(_media->model(), this);
  _controls = new Xe::Controls(_media, this);

  layout->addWidget(_view);
  layout->addWidget(_controls);
}
