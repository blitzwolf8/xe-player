#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QFileInfo>
#include <QObject>
#include <taglib/fileref.h>
#include <taglib/taglib.h>

namespace Xe {
class AudioInfo {
public:
  static QString getTitle(const QString &src) {
    auto str = src.toLocal8Bit().data();
    auto _filename = TagLib::FileName(str);
    auto ref = new TagLib::FileRef(_filename);

    if (QString(ref->tag()->title().toCString()) == "")
      return QFileInfo(src).fileName();
    else
      return QString(ref->tag()->title().toCString());
  }
  static QString getArtist(const QString &src) {
    auto str = src.toLocal8Bit().data();
    auto _filename = TagLib::FileName(str);
    auto ref = new TagLib::FileRef(_filename);
    return QString(ref->tag()->artist().toCString()).toUtf8();
  }
  static QString getFileName(const QString &src) { return src; }
};

} // namespace Xe

#endif
