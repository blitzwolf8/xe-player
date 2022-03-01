#ifndef XEWIDGET_H
#define XEWIDGET_H

#include <QWidget>

class XeWidget : public QWidget
{
    Q_OBJECT

public:
    XeWidget(QWidget *parent = nullptr);
    ~XeWidget();
};
#endif // XEWIDGET_H
