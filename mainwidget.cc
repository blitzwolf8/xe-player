#include "mainwidget.h"
#include "model.h"



Xe::AudioItem::AudioItem(QString &src, QObject *parent)
    : QObject(parent), source(src) {

    auto str = src.toLocal8Bit().data();
    ref = new TagLib::FileRef(str);

}


QString Xe::AudioItem::album() const {
    return QString(ref->tag()->album().toCString());
}

QString Xe::AudioItem::artist() const {
    return QString(ref->tag()->artist().toCString());
}

QString Xe::AudioItem::filename() const {
    return source;
}

QString Xe::AudioItem::title() const {
    return QString(ref->tag()->title().toCString());
}

Xe::AudioItem::~AudioItem(){}


Xe::PlaylistModel::PlaylistModel(QList<Xe::AudioItem> &_audioItems, QAbstractListModel *parent)
    : QAbstractListModel(parent), audioItems(_audioItems){}

int Xe::PlaylistModel::rowCount(const QModelIndex &/*parent*/) const {
    return audioItems.count();
}

QVariant Xe::PlaylistModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant();
    if(index.row() >= audioItems.size())
        return QVariant();
    if(role == Xe::Roles::TitleRole)
        return audioItems.at(index.row()).title();
    if(role == Xe::Roles::AlbumRole)
        return audioItems.at(index.row()).album();
    if(role == Xe::Roles::ArtistRole)
        return audioItems.at(index.row()).artist();
    if(role == Xe::Roles::FileRole)
        return audioItems.at(index.row()).filename();
    else
        return QVariant();
}

Xe::DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent){

    setMinimumSize(320,240);
    layout = new QVBoxLayout();
    setLayout(layout);

    listView = new QListView(this);
    listView->setModel(model);
    listView->setSelectionMode(QListView::SingleSelection);
    listView->setEditTriggers(QListView::NoEditTriggers);
    listView->setAlternatingRowColors(true);

    layout->addWidget(listView);
}

void Xe::DisplayWidget::setPlaylistModel(Xe::PlaylistModel *_model){
    model = _model;
}

Xe::ControlWidget::ControlWidget(QMediaPlayer *_player, QWidget *parent)
    : QWidget(parent), mediaPlayer(_player){


}


Xe::MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
}

Xe::MainWidget::~MainWidget()
{
}

