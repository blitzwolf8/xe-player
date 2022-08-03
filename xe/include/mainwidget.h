#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QVBoxLayout>
#include <QWidget>
#include <QtMultimedia/QMediaPlayer>

#include "model.h"
#include "view.h"
#include "controls.h"

namespace Xe {


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    QVBoxLayout *layout;
    Xe::ControlWidget *ctrlWidget;
    Xe::DisplayWidget *displayWidget;
    QMediaPlayer *mediaPlayer;
    QList<Xe::AudioItem> *_audioItems;
};



}


#endif // MAINWIDGET_H
