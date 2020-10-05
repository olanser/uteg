#include "file.h"
#include <QFile>

File::File(const QString& path)
{ 
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    if (!file.isReadable() || !file.isWritable())
        isMusic = false;
    else {
        TagLib::FileRef f(path.toUtf8().constData());

        if (!f.isNull()) {
           artist = f.tag()->artist().toCString();
           title = f.tag()->title().toCString();
           album = f.tag()->album().toCString();
           genre = f.tag()->genre().toCString();
           comment = f.tag()->comment().toCString();
           track = QString::number(f.tag()->track());
           year = QString::number(f.tag()->year());
           audioFilePath = path;
           isMusic = true;
        }
    }
    file.close();
}

QString File::getIdTeg(int idTeg) {
    switch (idTeg)
    {
        case 0:
            return artist;
            break;
        case 1:
            return title;
            break;
        case 2:
            return album;
            break;
        case 3:
            return genre;
            break;
        case 4:
            return comment;
            break;
        case 5:
            return track;
            break;
        case 6:
            return year;
            break;
        case 7:
            return audioFilePath;
            break;
    }
    return nullptr;
}

void File::setIdTeg(int idTeg, const QString& newValue) {
    switch (idTeg)
    {
        case 0:
            artist = newValue;
            break;
        case 1:
            title = newValue;
            break;
        case 2:
            album = newValue;
            break;
        case 3:
            genre = newValue;
            break;
        case 4:
            comment = newValue;
            break;
        case 5:
            track = newValue;
            break;
        case 6:
            year = newValue;
            break;
        case 7:
            audioFilePath = newValue;
            break;
    }
}

bool File::ifMusic(void) {
    return isMusic;
}
