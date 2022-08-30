#include "model.h"
#include "audioinfo.h"

#include <QDir>
#include <QDirIterator>

Xe::PlaylistModel::PlaylistModel(QAbstractListModel *parent)
    : QAbstractTableModel(parent) {
  folder = QDir::homePath().append("/Music");
  loadData(folder);
}

void Xe::PlaylistModel::loadData(const QString &dir) {
  beginResetModel();
  if (!audioItems.isEmpty()) {
    audioItems.clear();
  }
  auto _iter = QDirIterator(dir, QStringList() << "*.mp3", QDir::Files,
                            QDirIterator::Subdirectories);
  while (_iter.hasNext()) {
    audioItems.emplace_back(_iter.next());
  }
  audioItems.sort();
  endResetModel();
}

int Xe::PlaylistModel::rowCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : audioItems.size();
}

int Xe::PlaylistModel::columnCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : 2;
}

QVariant Xe::PlaylistModel::data(const QModelIndex &index, int role) const {

  const auto item = audioItems[(index.row())];
  if (!index.isValid())
    return QVariant();
  if (index.row() >= audioItems.size() || index.row() < 0)
    return QVariant();
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return AudioInfo::getTitle(item);
    case 1:
      return AudioInfo::getArtist(item);
    default:
      break;
    }
  }
  if (role == FileRole) {
    return AudioInfo::getFileName(item);
  }

  return QVariant();
}

QVariant Xe::PlaylistModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return tr("Title");
    case 1:
      return tr("Artist");
    default:
      break;
    }
  }
  return QVariant();
}

void Xe::PlaylistModel::setCurrentIndex(const QModelIndex &index) {
  _currentIndex = index;
  emit currentIndexChanged(_currentIndex);
}

QModelIndex Xe::PlaylistModel::currentIndex() const {
  return _currentIndex;
}