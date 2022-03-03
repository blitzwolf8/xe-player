#include "mainwidget.h"
#include "model.h"

#include <QDir>
#include <QDirIterator>



Xe::AudioItem::AudioItem( QString &src)
    : source(src) {

    auto str = src.toLocal8Bit().data();
    auto _filename = TagLib::FileName(str);

    ref = new TagLib::FileRef(_filename);



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
    if(role == Xe::Roles::TitleRole || role == Qt::DisplayRole)
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

Xe::DisplayWidget::DisplayWidget(Xe::PlaylistModel *_model, QWidget *parent)
    : QWidget(parent), model(_model){

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

Xe::DisplayWidget::~DisplayWidget(){}

Xe::ControlWidget::ControlWidget(QMediaPlayer *_player, QWidget *parent)
    : QWidget(parent), mediaPlayer(_player){

    setMinimumSize(320, 60);

    gridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();
    btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(0);

    setLayout(mainLayout);

    elpsdLbl = new QLabel("--:--");
    durationLbl = new QLabel("--:--");

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(mediaPlayer->duration()/1000);
    slider->setSliderPosition(0);

    auto playIc = QIcon(":/res/icons/play.png");
    auto stopIc = QIcon(":/res/icons/stop.png");
    auto nextIc = QIcon(":/res/icons/next.png");
    auto prevIc = QIcon(":/res/icons/back.png");
    auto pauseIc = QIcon(":/res/icons/pause.png");

    plpauseBtn = new QPushButton();
    plpauseBtn->setIcon(playIc);
    stopBtn = new QPushButton();
    stopBtn->setIcon(stopIc);
    nextBtn = new QPushButton();
    nextBtn->setIcon(nextIc);
    prevBtn = new QPushButton();
    prevBtn->setIcon(prevIc);

    gridLayout->addWidget(elpsdLbl, 0,0);
    gridLayout->addWidget(slider,0,1);
    gridLayout->addWidget(durationLbl, 0,2);

    btnLayout->setAlignment(Qt::AlignLeft);
    btnLayout->addWidget(plpauseBtn);
    btnLayout->addWidget(prevBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->addWidget(nextBtn);

    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,8));
    mainLayout->addLayout(btnLayout);


}

Xe::ControlWidget::~ControlWidget(){}


Xe::MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout();
    this->setLayout(layout);

    _audioItems = new QList<Xe::AudioItem>;

    auto _iter = QDirIterator(QDir::homePath().append("/Music/xy"),
                              QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
    while(_iter.hasNext()){
        auto _src = _iter.next();
        Xe::AudioItem a_itm(_src);
       _audioItems->push_back(a_itm);
    }

    model = new Xe::PlaylistModel(*_audioItems);
    mediaPositon = 0;

    auto _index = model->index(mediaPositon,0);


    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setSource(_index.data(Xe::Roles::FileRole).toUrl());

    displayWidget = new Xe::DisplayWidget(model, this);
    displayWidget->setPlaylistModel(model);
    ctrlWidget = new Xe::ControlWidget(mediaPlayer, this);

    layout->addWidget(displayWidget);
    layout->addWidget(ctrlWidget);

}

Xe::MainWidget::~MainWidget()
{
}

