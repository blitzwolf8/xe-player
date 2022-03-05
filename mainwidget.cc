#include "mainwidget.h"
#include "model.h"
#include "format.h"

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
    if(QString(ref->tag()->title().toCString()) == "")
        return QFileInfo(source).fileName();
    else
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

Xe::ControlWidget::ControlWidget(QMediaPlayer *_player, Xe::PlaylistModel *_model, QWidget *parent)
    : QWidget(parent), mediaPlayer(_player), model(_model){

    setMinimumSize(320, 60);

    gridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();
    btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(0);

    setLayout(mainLayout);

    m_pos = 0;
    auto _index = model->index(m_pos, 0);

    auto _audioOutput = new QAudioOutput();
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setAudioOutput(_audioOutput);
    mediaPlayer->setSource(_index.data(Xe::Roles::FileRole).toUrl());

    elpsdLbl = new QLabel("00:00");
    durationLbl = new QLabel("--:--");

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(mediaPlayer->duration()/1000);
    slider->setSliderPosition(0);

    plpauseBtn = new QPushButton();
    plpauseBtn->setIcon(QIcon(":/res/icons/play.png"));
    plpauseBtn->setIconSize({30,30});
    plpauseBtn->setStyleSheet("width: 32px; height:32px");
    stopBtn = new QPushButton();
    stopBtn->setIcon(QIcon(":/res/icons/stop.png"));
    stopBtn->setStyleSheet("width: 20px; height:20px");
    nextBtn = new QPushButton();
    nextBtn->setIcon(QIcon(":/res/icons/next.png"));
    nextBtn->setStyleSheet("width: 20px; height:20px");
    prevBtn = new QPushButton();
    prevBtn->setIcon(QIcon(":/res/icons/back.png"));
    prevBtn->setStyleSheet("width: 20px; height:20px");

    gridLayout->addWidget(elpsdLbl, 0,0);
    gridLayout->addWidget(slider,0,1);
    gridLayout->addWidget(durationLbl, 0,2);

    btnLayout->setAlignment(Qt::AlignLeft);
    btnLayout->addWidget(plpauseBtn);
    btnLayout->addSpacing(16);
    btnLayout->addWidget(prevBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->addWidget(nextBtn);

    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,8));
    mainLayout->addLayout(btnLayout);

    QObject::connect(plpauseBtn, &QPushButton::clicked, this, &ControlWidget::togglePlay);
    QObject::connect(stopBtn, &QPushButton::clicked, this, &ControlWidget::stopPlayer);
    QObject::connect(nextBtn, &QPushButton::clicked, this, &ControlWidget::nextTrack);
    QObject::connect(prevBtn, &QPushButton::clicked, this, &ControlWidget::previousTrack);
    QObject::connect(slider, &QSlider::sliderMoved, mediaPlayer, &QMediaPlayer::setPosition);
    QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);
    QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum);
    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &ControlWidget::mediaStatus);
    QObject::connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &ControlWidget::setDuration);
    QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &ControlWidget::trackPosition);

}

void Xe::ControlWidget::togglePlay() {

    if(mediaPlayer->playbackState() != QMediaPlayer::PlayingState){
        mediaPlayer->play();
        this->plpauseBtn->setIcon(QIcon(":/res/icons/pause.png"));
    }
    else{
        mediaPlayer->pause();
        this->plpauseBtn->setIcon(QIcon(":/res/icons/play.png"));
    }
}

void Xe::ControlWidget::stopPlayer(){

    if(mediaPlayer->playbackState() != QMediaPlayer::StoppedState){
        mediaPlayer->stop();
        this->plpauseBtn->setIcon(QIcon(":/res/icons/play.png"));
    }
}

void Xe::ControlWidget::nextTrack(){

    if(m_pos == (model->rowCount(QModelIndex()) - 1))
        m_pos = 0;
    else{m_pos += 1;}

    auto _index = model->index(m_pos,0);
    mediaPlayer->setSource(model->data(_index, Xe::Roles::FileRole).toUrl());
    mediaPlayer->play();
    plpauseBtn->setIcon(QIcon(":/res/icons/pause.png"));
}

void Xe::ControlWidget::previousTrack(){

    m_pos -= 1;
    if(m_pos < 0){
        m_pos = (model->rowCount(QModelIndex()) -1);
    }

    auto _index = model->index(m_pos,0);
    mediaPlayer->setSource(model->data(_index, Xe::Roles::FileRole).toUrl());
    mediaPlayer->play();
    plpauseBtn->setIcon(QIcon(":/res/icons/pause.png"));
}

void Xe::ControlWidget::mediaStatus() {

    if(mediaPlayer->mediaStatus() == QMediaPlayer::EndOfMedia && (mediaPlayer->loops() == 1)){
        nextTrack();
    }
}

void Xe::ControlWidget::setDuration(){
    auto _duration = mediaPlayer->duration();
    durationLbl->setText(formatTime(_duration));
}

void Xe::ControlWidget::trackPosition(){
    auto pos = mediaPlayer->position();
    elpsdLbl->setText(formatTime(pos));
}


Xe::ControlWidget::~ControlWidget(){}


Xe::MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout();
    this->setLayout(layout);

    _audioItems = new QList<Xe::AudioItem>;

    auto _iter = QDirIterator(QDir::homePath().append("/Music"),
                              QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
    while(_iter.hasNext()){
        auto _src = _iter.next();
        Xe::AudioItem a_itm(_src);
        _audioItems->push_back(a_itm);
    }

    auto _model = new Xe::PlaylistModel(*_audioItems);

    displayWidget = new Xe::DisplayWidget(_model, this);
    ctrlWidget = new Xe::ControlWidget(mediaPlayer, _model, this);

    layout->addWidget(displayWidget);
    layout->addWidget(ctrlWidget);

}

Xe::MainWidget::~MainWidget(){}











































