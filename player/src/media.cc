#include "media.h"

#include <QAudioOutput>
#include <QDir>
#include <QFileDialog>

Xe::Media::Media(QObject *parent) : QObject(parent), _index(0) {
  defaultFolder = QDir::homePath().append("Music");
  _model = new PlaylistModel();
  _player = new QMediaPlayer();
  auto aOut = new QAudioOutput(this);
  _player->setAudioOutput(aOut);
  loadMedia();

  QObject::connect(_player, &QMediaPlayer::mediaStatusChanged, this, &Media::status);
  QObject::connect(this, &Media::directoryChanged, _model, &PlaylistModel::loadData);
}

QMediaPlayer *Xe::Media::player() const { return _player; }

Xe::PlaylistModel *Xe::Media::model() const { return _model; }

void Xe::Media::loadMedia() {
  auto id = _model->index(_index, 0);
  auto playing = _model->data(id, PlaylistModel::FileRole);
  _model->setCurrentIndex(id);
  _player->setSource(playing.toString());
}

void Xe::Media::setState(MediaState state) {_state = state;}

Xe::MediaState Xe::Media::state() const {return _state;}

void Xe::Media::openDirectory() {
  auto dir = QFileDialog::getExistingDirectory(nullptr, "Choose Music Folder");
   if(!dir.isEmpty()){
     emit directoryChanged(dir);
   }
   loadMedia();
}

void Xe::Media::stopPlayback() {
  if(_player->playbackState() != QMediaPlayer::StoppedState){
    _player->stop();
    setState(MediaState::Stopped);
  }
}

void Xe::Media::tooglePlayback() {
  if(_player->playbackState() != QMediaPlayer::PlayingState){
    _player->play();
    setState(MediaState::Playing);
  }else {
    _player->pause();
    setState(MediaState::Paused);
  }
}

void Xe::Media::loadNext() {
  if (_index == (_model->rowCount(QModelIndex()) - 1))
    _index = 0;
  else {
    _index += 1;
  }

  auto idx = _model->index(_index, 0);
  _player->setSource(_model->data(idx, PlaylistModel::FileRole).toUrl());
  _player->play();
  setState(MediaState::Playing);
}

void Xe::Media::loadPrevious() {
  _index -= 1;
  if (_index < 0) {
    _index = (_model->rowCount(QModelIndex()) - 1);
  }

  auto idx = _model->index(_index, 0);
  _player->setSource(_model->data(idx, PlaylistModel::FileRole).toUrl());
  _player->play();
  setState(MediaState::Playing);
}

void Xe::Media::setMediaFolder(const QString &path) {}

qint64 Xe::Media::position() const { return _player->position(); }

qint64 Xe::Media::duration() const { return _player->duration(); }

void Xe::Media::status() {
  if (_player->mediaStatus() == QMediaPlayer::EndOfMedia &&
      (_player->loops() == 1)) {
    loadNext();
  }
  // if (_player->mediaStatus() == QMediaPlayer::LoadedMedia) {
  //   titleLabel->setText(
  //       model->index(m_pos, 0).data(PlaylistModel::TitleRole).toString());
  //   artistLabel->setText(
  //       model->index(m_pos, 0).data(PlaylistModel::ArtistRole).toString());
  // }
}
