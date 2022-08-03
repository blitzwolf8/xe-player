#include "model.h"





Xe::PlaylistModel::PlaylistModel(QList<Xe::AudioItem> &_audioItems,
                                 QAbstractListModel *parent)
    : QAbstractTableModel(parent), audioItems(_audioItems) {}

int Xe::PlaylistModel::rowCount(const QModelIndex & /*parent*/) const {
  return audioItems.count();
}

int Xe::PlaylistModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return 2;
}

QVariant Xe::PlaylistModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() >= audioItems.size())
    return QVariant();
  if (role == Xe::Roles::TitleRole || role == Qt::DisplayRole)
    return audioItems.at(index.row()).title();
  if (role == Xe::Roles::AlbumRole)
    return audioItems.at(index.row()).album();
  if (role == Xe::Roles::ArtistRole)
    return audioItems.at(index.row()).artist();
  if (role == Xe::Roles::FileRole)
    return audioItems.at(index.row()).filename();
  else
    return QVariant();
}

QVariant Xe::PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    if(section == 0)
      return "Title";
    if(section == 1)
      return "Artist";
  }
  return QVariant();
}

QHash<int, QByteArray> Xe::PlaylistModel::roleNames() const {
  QHash<int, QByteArray> roles;
  return roles;
}

