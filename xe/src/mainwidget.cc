#include "mainwidget.h"
#include "format.h"
#include "model.h"

#include <QDir>
#include <QDirIterator>

Xe::AudioItem::AudioItem(QString &src) : source(src) {

  auto str = src.toLocal8Bit().data();
  auto _filename = TagLib::FileName(str);

  ref = new TagLib::FileRef(_filename);
}

QString Xe::AudioItem::album() const {
  return QString(ref->tag()->album().toCString());
}

QString Xe::AudioItem::artist() const {
  return QString(ref->tag()->artist().toCString());
}

QString Xe::AudioItem::filename() const { return source; }

QString Xe::AudioItem::title() const {
  if (QString(ref->tag()->title().toCString()) == "")
    return QFileInfo(source).fileName();
  else
    return QString(ref->tag()->title().toCString());
}

Xe::AudioItem::~AudioItem() {}


Xe::MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  layout = new QVBoxLayout();
  this->setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);

  _audioItems = new QList<Xe::AudioItem>;

  auto _iter =
      QDirIterator(QDir::homePath().append("/Music"), QStringList() << "*.mp3",
                   QDir::Files, QDirIterator::Subdirectories);
  while (_iter.hasNext()) {
    auto _src = _iter.next();
    Xe::AudioItem a_itm(_src);
    _audioItems->push_back(a_itm);
  }

  auto _model = new Xe::PlaylistModel(*_audioItems);

  displayWidget = new Xe::DisplayWidget(_model, this);
  ctrlWidget = new Xe::ControlWidget(mediaPlayer, _model, this);

  layout->addWidget(displayWidget);
  layout->addWidget(ctrlWidget);
}

Xe::MainWidget::~MainWidget() {}
