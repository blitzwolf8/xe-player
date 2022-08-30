#ifndef CONTROLS_H
#define CONTROLS_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QListView>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

#include "media.h"
#include "model.h"

namespace Xe {

class PlaylistModel;

class Controls : public QWidget {
  Q_OBJECT
public:
  Controls(Media *media, QWidget *parent = nullptr);
  void setMediaPlayer(QMediaPlayer *_player);

public slots:
  void togglePlay();
  void toggleShuffle();
  void stopPlayer();
  void nextTrack();
  void previousTrack();
  void setDuration();
  void trackPosition();

private:
  QGridLayout *gridLayout;
  QHBoxLayout *btnLayout;
  QLabel *durationLbl;
  QLabel *elpsdLbl;
  QPushButton *nextBtn;
  QPushButton *plpauseBtn;
  QPushButton *prevBtn;
  QPushButton *stopBtn;
  QPushButton * shuffleBtn;
  QSlider *slider;
  QVBoxLayout *mainLayout;
  Xe::PlaylistModel *model;
  qint64 m_pos;
  Media *_media;
};

} // namespace Xe

#endif
