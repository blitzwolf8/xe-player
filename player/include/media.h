#ifndef MEDIA_H
#define MEDIA_H

#include "model.h"
#include <QMediaPlayer>

namespace Xe {
class Media : public QObject {
  Q_OBJECT
  Q_ENUMS(MediaState)
public:
  enum class MediaState {Playing, Stopped, Paused};
  explicit Media(QObject *parent = nullptr);

  QMediaPlayer* player() const;
  PlaylistModel* model() const;
  qint64 position() const;
  qint64 duration() const;
  void setSource();
  void setMediaFolder(const QString& path);
  void setState(MediaState state);
  MediaState state() const;

signals:
  void directoryChanged(const QString&);

public slots:
  void loadMedia();
  void openDirectory();
  void loadNext();
  void loadPrevious();
  void stopPlayback();
  void tooglePlayback();
  void status();

private:
  QMediaPlayer *_player;
  quint64 _index;
  QString defaultFolder;
  PlaylistModel *_model;
  MediaState _state;
};

using MediaState = Media::MediaState;

} // namespace Xe

#endif
