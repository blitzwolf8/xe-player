#include "xewidget.h"
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
    if(role == Qt::DisplayRole)
        return audioItems.at(index.row()).title();
    else
        return QVariant();
}


XeWidget::XeWidget(QWidget *parent)
    : QWidget(parent)
{
}

XeWidget::~XeWidget()
{
}

