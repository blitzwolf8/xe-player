#include "view.h"




Xe::DisplayWidget::DisplayWidget(Xe::PlaylistModel *_model, QWidget *parent)
    : QWidget(parent), model(_model) {

  setMinimumSize(640, 280);
  layout = new QVBoxLayout();
  setLayout(layout);

  _tableView = new QTableView(this);
  _tableView->setModel(model);
  _tableView->setSelectionMode(QTableView::SingleSelection);
  _tableView->setEditTriggers(QTableView::NoEditTriggers);
  _tableView->setAlternatingRowColors(true);

  layout->addWidget(_tableView);
}

void Xe::DisplayWidget::setPlaylistModel(Xe::PlaylistModel *_model) {
  model = _model;
}

Xe::DisplayWidget::~DisplayWidget() {}
