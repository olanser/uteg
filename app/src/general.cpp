#include "general.h"

General::General(QTableWidget *newTable, QTextBrowser * newTextBrowser) : table(newTable),
    notFound(newTextBrowser)
{
    notFound->setTextColor(QColor(255,0,0));
    notFound->setFontPointSize(36);
}

void General::setPath(const QString& path) {
    isEditTable = true;
    this->files.resize(0);
    QDir dir(path);
    if (!dir.exists()) {
        setErrorArgv();
        return;
    }
    QStringList filters(QStringList() << "*.mp3"
                                     << "*.ogg"
                                     << "*.wav"
                                     << "*.flac");
    dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList(QDir::Files |
                                           QDir::Hidden |
                                           QDir::NoSymLinks);
    foreach (QFileInfo finfo, list) {
        File temp(finfo.absoluteFilePath());
        if (temp.ifMusic())
            files.push_back(temp);
    }
    table->clearContents();
    table->setSortingEnabled(false);
    table->setRowCount(files.size());
    for (int i = 0; i < files.size(); ++i) {
        table->setItem(i, 8, new QTableWidgetItem(QString::number(i), 0));
        for (int id = 0; id < 8; ++id)
            table->setItem(i, id, new QTableWidgetItem(files[i].getIdTeg(id), 0));
        table->item(i, 7)->setFlags(table->item(i, 7)->flags() & ~Qt::ItemIsEditable);
    }
    table->setSortingEnabled(true);
    table->hideColumn(8);
    notFound->setText("NOT FOUND!!!");
    notFound->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    if (files.size() > 0) {
        if (notFound->isVisible())
            notFound->hide();
        if (!table->isVisible())
            table->show();
    }
    else {
        if (!notFound->isVisible())
            notFound->show();
        if (table->isVisible())
            table->hide();
    }
    paths = path;
    isEditTable = false;
}

void General::addNewChenge(int idFile, int idTeg, int row, const QString &newValue) {
    if (idTeg == 5 || idTeg == 6 ) {
        for (int i = 0; i < newValue.size(); ++i) {
            if (!newValue[i].isDigit()) {
                table->item(row, idTeg)->setText(files[idFile].getIdTeg(idTeg));
                return;
            }          
        }
    }
    chengeFile[{idFile, idTeg}] = newValue;
}

void General::saveChange(void) {
    QMap<QPair<int,int>, QString>::const_iterator i = chengeFile.constBegin();
    while (i != chengeFile.constEnd()) {      
        TagLib::FileRef f(files[i.key().first].getIdTeg(7).toUtf8().data());

        if (!f.isNull()) {
            switch (i.key().second)
            {
            case 0:
                f.tag()->setArtist(i.value().toUtf8().data());
                break;
            case 1:
                f.tag()->setTitle(i.value().toUtf8().data());
                break;
            case 2:
                f.tag()->setAlbum(i.value().toUtf8().data());
                break;
            case 3:
                f.tag()->setGenre(i.value().toUtf8().data());
                break;
            case 4:
                f.tag()->setComment(i.value().toUtf8().data());
                break;
            case 5:
                f.tag()->setTrack(i.value().toInt());
                break;
            case 6:
                f.tag()->setYear(i.value().toInt());
                break;
            default:
                break;
            }
            if (i.key().second >= 0 && i.key().second <= 6)
                files[i.key().first].setIdTeg(i.key().second, i.value());
            f.save();
        }
        ++i;
    }
    chengeFile.clear();
}

void General::cancel(void) {
    chengeFile.clear();
    table->clearContents();
    table->setRowCount(files.size());
    table->setSortingEnabled(false);
    for (int i = 0; i < files.size(); ++i) {
        table->setItem(i, 8, new QTableWidgetItem(QString::number(i), 0));
        for (int id = 0; id < 8; ++id)
            table->setItem(i, id, new QTableWidgetItem(files[i].getIdTeg(id), 0));
        table->item(i, 7)->setFlags(table->item(i, 7)->flags() & ~Qt::ItemIsEditable);
    }
    table->setSortingEnabled(true);
}

void General::update(void) {
    setPath(paths);
}

bool General::ifEditTable(void) {
    return !isEditTable;
}

void General::setErrorArgv(void) {
    if (table->isVisible())
            table->hide();
    notFound->setText("usage: \"./utag [directory]\"!!!");
    notFound->setAlignment(Qt::AlignCenter);
}
