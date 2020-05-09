#ifndef FILE_H
#define FILE_H

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif
#include <QDir>
#include <QMap>
#include <QDate>
#include <QList>
#include <QDebug>
static QMap<QDate,QMap<QString,QList<QString>>> Tmp;
static QMap<QDate,QMap<QString,QTime>> Tmp1;
class File
{
public:
    File();
    //储存事件清单
    bool save(QMap<QDate,QMap<QString,QList<QString>>> &DateList = Tmp);

    //读取事件清单
    bool read(QMap<QDate,QMap<QString,QList<QString>>> &DateList = Tmp);

    //储存需要提醒的事件清单
    void notification_save(QMap<QDate,QMap<QString,QTime>> &RemindList = Tmp1);

    //读取需要提醒的事件清单
    void notification_read(QMap<QDate,QMap<QString,QTime>> &RemindList = Tmp1);
private:
    //文件名
    QString FileName;
    //文件路径
    QString FilePath;
};

#endif // FILE_H
