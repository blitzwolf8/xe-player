#ifndef VIEW_H
#define VIEW_H

#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

#include "model.h"

namespace Xe {

class PlaylistModel;

class View : public QWidget {
  Q_OBJECT

public:
  View(PlaylistModel *_model, QWidget *parent = nullptr);
  void setPlaylistModel(Xe::PlaylistModel *_model);
  void updateSelection(const QModelIndex&);

private:
  QTableView *_tableView;
  PlaylistModel *model;
  QVBoxLayout *layout;
};

} // namespace Xe

#endif
