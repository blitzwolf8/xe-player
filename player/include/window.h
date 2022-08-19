#ifndef WINDOW_H
#define WINDOW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QtMultimedia/QMediaPlayer>

#include "controls.h"
#include "media.h"
#include "model.h"
#include "view.h"

namespace Xe {

class Window : public QWidget {
  Q_OBJECT

public:
  Window(QWidget *parent = nullptr);

private:
  QVBoxLayout *layout;
  Controls *_controls;
  View *_view;
  Media *_media;
};

} // namespace Xe

#endif // WINDOW_H
