#include "controls.h"
#include "format.h"

#include <QAction>

Xe::Controls::Controls(Media *media, QWidget *parent)
    : QWidget(parent), _media(media) {

  setMinimumSize(640, 80);

  gridLayout = new QGridLayout();
  mainLayout = new QVBoxLayout();
  btnLayout = new QHBoxLayout();
  btnLayout->setSpacing(0);

  setLayout(mainLayout);

  auto mediaPlayer = _media->player();
  model = _media->model();

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
  shuffleBtn = new QPushButton();
  shuffleBtn->setIcon(QIcon(":/icons/stop.png"));
  shuffleBtn->setToolTip("Shuffle playlist");
  shuffleBtn->setCheckable(true);

  gridLayout->addWidget(elpsdLbl, 0, 0);
  gridLayout->addWidget(slider, 0, 1);
  gridLayout->addWidget(durationLbl, 0, 2);

  btnLayout->setAlignment(Qt::AlignLeft);
  btnLayout->addWidget(plpauseBtn);
  btnLayout->addSpacing(16);
  btnLayout->addWidget(prevBtn);
  btnLayout->addWidget(stopBtn);
  btnLayout->addWidget(nextBtn);
  btnLayout->addSpacing(16);
  btnLayout->addWidget(shuffleBtn);
  mainLayout->addLayout(gridLayout);
  mainLayout->addSpacerItem(new QSpacerItem(0, 8));
  mainLayout->addLayout(btnLayout);

  auto _open = new QAction();
  addAction(_open);
  _open->setShortcut(QKeySequence::Open);
  QObject::connect(_open, &QAction::triggered, _media, &Media::openDirectory);

  QObject::connect(plpauseBtn, &QPushButton::clicked, this,
                   &Controls::togglePlay);
  QObject::connect(stopBtn, &QPushButton::clicked, this,
                   &Controls::stopPlayer);
  QObject::connect(nextBtn, &QPushButton::clicked, this,
                   &Controls::nextTrack);
  QObject::connect(prevBtn, &QPushButton::clicked, this,
                   &Controls::previousTrack);
  QObject::connect(slider, &QSlider::sliderMoved, mediaPlayer,
                   &QMediaPlayer::setPosition);
  QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, slider,
                   &QSlider::setValue);
  QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, slider,
                   &QSlider::setMaximum);
  QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, this,
                   &Controls::setDuration);
  QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, this,
                   &Controls::trackPosition);
  QObject::connect(shuffleBtn, &QPushButton::released , this, &Controls::toggleShuffle);
  QObject::connect(_media, &Media::mediaStateChanged, [this] {
    if (_media->state() == MediaState::Paused || _media->state() == MediaState::Stopped) {
      plpauseBtn->setIcon(QIcon(":/icons/play.png"));
    } else {
      plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
    }
  });
}

void Xe::Controls::togglePlay() {
  _media->tooglePlayback();
}

void Xe::Controls::toggleShuffle() {
  if (shuffleBtn->isChecked() == false) {
    shuffleBtn->setChecked(false);
    // model->shuffle();
  } else {
    shuffleBtn->setChecked(true);
    // model->shuffle();
  }
}

void Xe::Controls::stopPlayer() {

  if (_media->state() != Media::MediaState::Stopped) {
    _media->stopPlayback();
    this->plpauseBtn->setIcon(QIcon(":/icons/play.png"));
  }
}

void Xe::Controls::nextTrack() {
  _media->loadNext();
  if (_media->state() == Media::MediaState::Playing)
    plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
}

void Xe::Controls::previousTrack() {

  _media->loadPrevious();
  if (_media->state() == Media::MediaState::Playing)
    plpauseBtn->setIcon(QIcon(":/icons/pause.png"));
}

void Xe::Controls::setDuration() {
  auto _duration = _media->duration();
  durationLbl->setText(formatTime(_duration));
}

void Xe::Controls::trackPosition() {
  auto pos = _media->position();
  elpsdLbl->setText(formatTime(pos));
}
