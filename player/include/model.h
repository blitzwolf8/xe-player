#ifndef MODEL_H
#define MODEL_H

#include "audioinfo.h"

#include <QAbstractTableModel>

namespace Xe {

class PlaylistModel : public QAbstractTableModel {
  Q_OBJECT
  Q_ENUMS(Roles)

public:
  enum Roles { TitleRole = Qt::UserRole, ArtistRole, FileRole };
  PlaylistModel(QAbstractListModel *parent = nullptr);

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex currentIndex() const;

signals:
  void currentIndexChanged(const QModelIndex& index);

public slots:
  void setCurrentIndex(const QModelIndex &);
  void loadData(const QString &);

private:
  QStringList audioItems;
  QString folder;
  QModelIndex _currentIndex;
  AudioInfo *info;
};

} // end namespace Xe

#endif // MODEL_H
