#ifndef FILE_H
#define FILE_H

#include <QString>
#include <tbytevector.h>

#include <mpegfile.h>

#include <id3v2tag.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <commentsframe.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>


#include <id3v1tag.h>

#include <apetag.h>
class File
{
public:
    File(const QString& path = "1");

    QString getIdTeg(int idTeg);
    void setIdTeg(int idTeg, const QString& newValue);
    bool ifMusic(void);
private:
    QString artist;
    QString title;
    QString album;
    QString genre;
    QString audioFilePath;
    QString comment;
    QString track;
    QString year;
    bool isMusic = false;
};

#endif // FILE_H
