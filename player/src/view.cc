#include "view.h"

#include <QAbstractItemView>
#include <QHeaderView>

Xe::View::View(PlaylistModel *_model, QWidget *parent)
    : QWidget(parent), model(_model) {
  setMinimumSize(640, 280);
  layout = new QVBoxLayout();
  setLayout(layout);

  setStyleSheet(
      "QTableView {selection-background-color : "
      "#414141;qproperty-showGrid : false; }");

  _tableView = new QTableView(this);
  _tableView->setModel(model);
  _tableView->setSelectionMode(QTableView::SingleSelection);
  _tableView->setEditTriggers(QTableView::NoEditTriggers);
  _tableView->setAlternatingRowColors(true);
  _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  _tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  _tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  _tableView->horizontalHeader()->setFirstSectionMovable(false);
  _tableView->horizontalHeader()->setStretchLastSection(true);
  _tableView->horizontalHeader()->setSectionsClickable(true);
  _tableView->horizontalHeader()->setSectionsMovable(true);
  _tableView->verticalHeader()->hide();

  layout->addWidget(_tableView);
  QObject::connect(_tableView, &QTableView::doubleClicked, model,
                   &PlaylistModel::setCurrentIndex);
  QObject::connect(model, &PlaylistModel::currentIndexChanged, this,
                   &View::updateSelection);
}

void Xe::View::setPlaylistModel(Xe::PlaylistModel *_model) { model = _model; }

void Xe::View::updateSelection(const QModelIndex &index) {
  qDebug() << "updating selection for row " << index.row();
  _tableView->selectionModel()->select(
      index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
}