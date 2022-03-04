#include "format.h"




QString Xe::formatHms(qint64 time){
    if(time == 0)
        return "00";
    if(time < 10)
        return QString("0").append(QString::number(time));
    else
        return QString::number(time);
}

QString Xe::formatTime(qint64 _time){
    auto time = _time / 1000;
    auto hours = qFloor(time / 3600);
    time = time - hours * 3600;
    auto minutes = qFloor(time / 60);
    auto seconds = qFloor(time - minutes * 60);
    if(hours == 0)
        return formatHms(minutes).append(":").append(formatHms(seconds));
    else
        return formatHms(hours).append(":").append(formatHms(minutes)).append(":").append(formatHms(seconds));
}
