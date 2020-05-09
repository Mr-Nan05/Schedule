#include "file.h"
File::File()
{
    FilePath = QDir::currentPath() + "/history";
}


bool File::save(QMap<QDate,QMap<QString,QList<QString>>> &DateList)
{
    foreach(const QDate &date,DateList.keys()){
        QDir Folder;
        QString FolderName = QDir::currentPath() +  "/history" + date.toString("/yyyy_MM_dd");

        if(!Folder.mkpath(FolderName))
            continue;
        else {
            foreach(const QString &EventName, DateList[date].keys()){
                    FileName = FolderName + "/" + EventName + ".log";
                    QFile aEvent(FileName);
                    if(aEvent.exists()){
                        QString Remove = FileName.toUtf8();
                        QFile::remove(Remove);
                    }
                    aEvent.open(QIODevice::ReadWrite|QIODevice::Text);
                    foreach(const QString &Incident, DateList[date][EventName]){
                        QByteArray str = Incident.toUtf8();
                        aEvent.write(str);
                        aEvent.write("\n\r");
                    }
                    aEvent.close();
            }
        }
    }
    return true;
}

void File::notification_save(QMap<QDate,QMap<QString,QTime>> &RemindList)
{
    foreach(const QDate &date, RemindList.keys()){
        QDir Folder;
        QString FolderName = QDir::currentPath() + "/notifications" + date.toString("/yyyy_MM_dd");

        if(!Folder.mkpath(FolderName))
            continue;
        else {
            foreach(const QString &EventName, RemindList[date].keys()){
                FileName = FolderName + '/' + EventName + ".log";
                QFile aEvent(FileName);
                if(aEvent.exists()){
                    QString Remove = FileName.toUtf8();
                    QFile::remove(Remove);
                }
                aEvent.open(QIODevice::ReadWrite|QIODevice::Text);
                QByteArray NotificationTime = RemindList[date][EventName].toString("hh:mm:ss").toUtf8();
                aEvent.write(NotificationTime);
                aEvent.close();
            }
        }
    }
}

void File::notification_read(QMap<QDate,QMap<QString,QTime>> &RemindList)
{
    RemindList.clear();
    QDir Folder(QDir::currentPath() + "/notifications");
    if(Folder.exists()){
        Folder.setFilter(QDir::Dirs);
        QFileInfoList FolderList = Folder.entryInfoList();
        foreach(const QFileInfo &EventDate,FolderList){
            if(EventDate.isDir()){
                QString aDateName = EventDate.fileName();
                if(aDateName == "."||aDateName == "..")
                    continue;
                QString CurrentFilePath = QDir::currentPath() + "/notifications" +'/' + aDateName;
                QDir aDateFolder(CurrentFilePath);
                if(!aDateFolder.exists())
                    continue;
                aDateFolder.setFilter(QDir::Files);
                QFileInfoList FileList = aDateFolder.entryInfoList();
                QMap<QString, QTime> aDateEvent;
                foreach(const QFileInfo &Event,FileList){
                    QString aEventName = Event.fileName();
                    QString aEventPath =  CurrentFilePath + '/' + aEventName;
                    QFile aEvent(aEventPath);
                    if(!aEvent.exists())
                        continue;
                    if(!aEvent.open(QIODevice::ReadOnly | QIODevice::Text))
                        continue;
                    QTextStream aEventStream(&aEvent);
                    QString aTime = aEventStream.readLine();
                    aEvent.close();
                    aEventName = aEventName.mid(0,aEventName.length() - 4);
                    QString aHour = aTime.mid(0,2),aMin,aSec = aTime.mid(6,8);
                    aMin = aMin + aTime[3] + aTime[4];
                    QTime theTime(aHour.toInt(),aMin.toInt(),aSec.toInt());
                    //theTime.fromString(aTime,"hh:mm:ss");
                    aDateEvent[aEventName] = theTime;
                }

                //aDate.fromString(aDateName,"yyyy_MM_dd");
                QString aYear,aMonth,aDay;
                aYear = aDateName.mid(0,4);
                aMonth = aMonth + aDateName[5] + aDateName[6];
                aDay = aDateName.mid(8,10);
                QDate aDate(aYear.toInt(),aMonth.toInt(),aDay.toInt());
                RemindList[aDate] = aDateEvent;
                QDir DeleteDir = aDateFolder;
                DeleteDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

                QFileInfoList fileList = DeleteDir.entryInfoList();
                foreach (QFileInfo fi, fileList)
                    if (fi.isFile())
                        fi.dir().remove(fi.fileName());
            }
        }
    }
}

bool File::read(QMap<QDate,QMap<QString,QList<QString>>> &DateList)
{
    DateList.clear();
    QDir Folder(FilePath);
    if(!Folder.exists())
        return false;

    Folder.setFilter(QDir::Dirs);
    QFileInfoList FolderList = Folder.entryInfoList();
    foreach(const QFileInfo &EventDate,FolderList){
        if(EventDate.isDir()){
            QString aDateName = EventDate.fileName();
            if(aDateName == "."||aDateName == "..")
                continue;
            QString CurrentFilePath = FilePath +'/' + aDateName;

            QDir aDateFolder(CurrentFilePath);
            if(!aDateFolder.exists())
                continue;

            aDateFolder.setFilter(QDir::Files);
            QFileInfoList FileList = aDateFolder.entryInfoList();

            QMap<QString,QList<QString>> aDateEvent;
            foreach(const QFileInfo &Event,FileList){
                QString aEventName = Event.fileName();
                QString aEventPath =  CurrentFilePath + '/' + aEventName;
                QFile aEvent(aEventPath);
                if(!aEvent.exists())
                    continue;

                if(!aEvent.open(QIODevice::ReadOnly | QIODevice::Text))
                    continue;

                QTextStream aEventStream(&aEvent);
                QList<QString> aIncidentList;
                while(!aEventStream.atEnd()){
                    QString aIncident = aEventStream.readLine();
                    aIncidentList.push_back(aIncident);
                }
                aEvent.close();
                aEventName = aEventName.mid(0,aEventName.length() - 4);

                aDateEvent[aEventName] = aIncidentList;
            }
            QString aYear,aMonth,aDay;
            aYear = aDateName.mid(0,4);
            aMonth = aMonth + aDateName[5] + aDateName[6];
            aDay = aDateName.mid(8,10);

            QDate aDate(aYear.toInt(),aMonth.toInt(),aDay.toInt());
            DateList[aDate] = aDateEvent;

            QDir DeleteDir = aDateFolder;
            DeleteDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

            QFileInfoList fileList = DeleteDir.entryInfoList();
            foreach (QFileInfo fi, fileList)
                if (fi.isFile())
                    fi.dir().remove(fi.fileName());
        }
    }
    return true;
}
