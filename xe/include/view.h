#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>

#include "model.h"

namespace Xe{

class PlaylistModel;

class DisplayWidget : public QWidget {
    Q_OBJECT

public:
    DisplayWidget(PlaylistModel *_model ,QWidget *parent=nullptr);
    ~DisplayWidget();
    void setPlaylistModel(Xe::PlaylistModel *_model);

private:
    QTableView *_tableView;
    Xe::PlaylistModel *model;
    QVBoxLayout *layout;
};

}

#endif
