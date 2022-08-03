#include "controls.h"
#include "format.h"

Xe::ControlWidget::ControlWidget(QMediaPlayer *_player,
                                 Xe::PlaylistModel *_model, QWidget *parent)
    : QWidget(parent), mediaPlayer(_player), model(_model) {

  setMinimumSize(640, 80);

  gridLayout = new QGridLayout();
  mainLayout = new QVBoxLayout();
  btnLayout = new QHBoxLayout();
  btnLayout->setSpacing(0);

  setLayout(mainLayout);

  m_pos = 0;
  auto _index = model->index(m_pos, 0);

  auto _audioOutput = new QAudioOutput();
  mediaPlayer = new QMediaPlayer();
  mediaPlayer->setAudioOutput(_audioOutput);
  mediaPlayer->setSource(_index.data(Xe::Roles::FileRole).toUrl());

  elpsdLbl = new QLabel("00:00");
  durationLbl = new QLabel("--:--");

  slider = new QSlider(Qt::Horizontal);
  slider->setMinimum(0);
  slider->setMaximum(mediaPlayer->duration() / 1000);
  slider->setSliderPosition(0);

  plpauseBtn = new QPushButton();
  plpauseBtn->setIcon(QIcon(":/icons/play.png"));
  plpauseBtn->setIconSize({30, 30});
  plpauseBtn->setStyleSheet("width: 32px; height:32px");
  plpauseBtn->setToolTip("Play");
  stopBtn = new QPushButton();
  stopBtn->setIcon(QIcon(":/icons/stop.png"));
  stopBtn->setStyleSheet("width: 20px; height:20px");
  stopBtn->setToolTip("Stop Playback");
  nextBtn = new QPushButton();
  nextBtn->setIcon(QIcon(":/icons/next.png"));
  nextBtn->setStyleSheet("width: 20px; height:20px");
  nextBtn->setToolTip("Next media");
  prevBtn = new QPushButton();
  prevBtn->setIcon(QIcon(":/icons/back.png"));
  prevBtn->setStyleSheet("width: 20px; height:20px");
  prevBtn->setToolTip("Previous media");

  titleLabel = new QLabel("Title");
  titleLabel->setStyleSheet("font-size: 14px");
  artistLabel = new QLabel("Artist");
  artistLabel->setStyleSheet("font-size: 12px");

  gridLayout->addWidget(elpsdLbl, 0, 0);
  gridLayout->addWidget(slider, 0, 1);
  gridLayout->addWidget(durationLbl, 0, 2);

  btnLayout->setAlignment(Qt::AlignLeft);
  btnLayout->addWidget(plpauseBtn);
  btnLayout->addSpacing(16);
  btnLayout->addWidget(prevBtn);
  btnLayout->addWidget(stopBtn);
  btnLayout->addWidget(nextBtn);

  mainLayout->addWidget(titleLabel);
  mainLayout->addWidget(artistLabel);
  mainLayout->addLayout(gridLayout);
  mainLayout->addSpacerItem(new QSpacerItem(0, 8));
  mainLayout->addLayout(btnLayout);

  QObject::connect(plpauseBtn, &QPushButton::clicked, this,
                   &ControlWidget::togglePlay);
  QObject::connect(stopBtn, &QPushButton::clicked, this,
                   &ControlWidget::stopPlayer);
  QObject::connect(nextBtn, &QPushButton::clicked, this,
                   &ControlWidget::nextTrack);
  QObject::connect(prevBtn, &QPushButton::clicked, this,
                   &ControlWidget::previousTrack);
  QObject::connect(slider, &QSlider::sliderMoved, mediaPlayer,
                   &QMediaPlayer::setPosition);
  QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, slider,
                   &QSlider::setValue);
  QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, slider,
                   &QSlider::setMaximum);
  QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
                   &ControlWidget::mediaStatus);
  QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, this,
                   &ControlWidget::setDuration);
  QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, this,
                   &ControlWidget::trackPosition);
}

void Xe::ControlWidget::togglePlay() {

  if (mediaPlayer->playbackState() != QMediaPlayer::PlayingState) {
    mediaPlayer->play();
    this->plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
  } else {
    mediaPlayer->pause();
    this->plpauseBtn->setIcon(QIcon(":/icons/play.png"));
  }
}

void Xe::ControlWidget::stopPlayer() {

  if (mediaPlayer->playbackState() != QMediaPlayer::StoppedState) {
    mediaPlayer->stop();
    this->plpauseBtn->setIcon(QIcon(":/icons/play.png"));
  }
}

void Xe::ControlWidget::nextTrack() {

  if (m_pos == (model->rowCount(QModelIndex()) - 1))
    m_pos = 0;
  else {
    m_pos += 1;
  }

  auto _index = model->index(m_pos, 0);
  mediaPlayer->setSource(model->data(_index, Xe::Roles::FileRole).toUrl());
  mediaPlayer->play();
  plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
}

void Xe::ControlWidget::previousTrack() {

  m_pos -= 1;
  if (m_pos < 0) {
    m_pos = (model->rowCount(QModelIndex()) - 1);
  }

  auto _index = model->index(m_pos, 0);
  mediaPlayer->setSource(model->data(_index, Xe::Roles::FileRole).toUrl());
  mediaPlayer->play();
  plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
}

void Xe::ControlWidget::mediaStatus() {

  if (mediaPlayer->mediaStatus() == QMediaPlayer::EndOfMedia &&
      (mediaPlayer->loops() == 1)) {
    nextTrack();
  }
  if (mediaPlayer->mediaStatus() == QMediaPlayer::LoadedMedia) {
    titleLabel->setText(
        model->index(m_pos, 0).data(Xe::Roles::TitleRole).toString());
    artistLabel->setText(
        model->index(m_pos, 0).data(Xe::Roles::ArtistRole).toString());
  }
}

void Xe::ControlWidget::setDuration() {
  auto _duration = mediaPlayer->duration();
  durationLbl->setText(formatTime(_duration));
}

void Xe::ControlWidget::trackPosition() {
  auto pos = mediaPlayer->position();
  elpsdLbl->setText(formatTime(pos));
}

Xe::ControlWidget::~ControlWidget() {}