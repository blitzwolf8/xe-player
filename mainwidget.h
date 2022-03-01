#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QListView>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

#include "model.h"

namespace Xe {

class DisplayWidget : QWidget {
    Q_OBJECT
public:
    DisplayWidget(QWidget *parent=nullptr);
    void setPlaylistModel(Xe::PlaylistModel *_model);
private:
    QListView *listView;
    Xe::PlaylistModel *model;
    QVBoxLayout *layout;
};

class ControlWidget : QWidget {
    Q_OBJECT
public:
    ControlWidget(QMediaPlayer *_player, QWidget *parent=nullptr);
    void setMediaPlayer(QMediaPlayer *_player);
private:
    QGridLayout *gridLayout;
    QHBoxLayout *btnLayout;
    QLabel *durationLbl;
    QLabel *elpsdLbl;
    QPushButton *nextBtn;
    QPushButton *plpauseBtn;
    QPushButton *prevBtn;
    QPushButton *stopBtn;
    QSlider *slider;
    QVBoxLayout *mainLayout;
    QMediaPlayer *mediaPlayer;

};


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};



}


#endif // MAINWIDGET_H
