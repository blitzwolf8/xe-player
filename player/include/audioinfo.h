#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QFileInfo>
#include <QObject>
#include <taglib/fileref.h>
#include <taglib/taglib.h>

namespace Xe {
class AudioInfo {
public:

  AudioInfo* operator()(const QString& filename) {
    auto str = filename.toLocal8Bit().data();
    _filename = TagLib::FileName(str);
    ref = TagLib::FileRef(_filename);

    return this;
  }

  QString getTitle() {
    if (QString(ref.tag()->title().toCString()) == "")
      return QFileInfo(_filename).fileName();
    else
      return QString(ref.tag()->title().toCString());
  }
  QString getArtist() {
    return QString(ref.tag()->artist().toCString()).toUtf8();
  }
  QString getFileName() { return QString(_filename); }

  private:
    TagLib::FileRef ref;
    const char* _filename;
};

} // namespace Xe

#endif
