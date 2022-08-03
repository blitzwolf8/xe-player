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

#include "model.h"

namespace Xe {

class PlaylistModel;

class ControlWidget : public QWidget {
  Q_OBJECT
public:
  ControlWidget(QMediaPlayer *_player, PlaylistModel *_model,
                QWidget *parent = nullptr);
  ~ControlWidget();
  void setMediaPlayer(QMediaPlayer *_player);

public slots:
  void togglePlay();
  void stopPlayer();
  void nextTrack();
  void previousTrack();
  void mediaStatus();
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
  QSlider *slider;
  QVBoxLayout *mainLayout;
  QMediaPlayer *mediaPlayer;
  Xe::PlaylistModel *model;
  qint64 m_pos;
  QLabel *titleLabel;
  QLabel *artistLabel;
};

} // namespace Xe

#endif
