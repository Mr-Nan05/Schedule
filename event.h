#ifndef EVENT_H
#define EVENT_H
#include <QCloseEvent>
#include <QDialog>
#include <QList>
#include "incident.h"
#include "ui_event.h"

static QList<QString> Tmp0;

namespace Ui {
class Event;
}

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(QWidget *parent = nullptr);
    Event(QWidget *parent = nullptr,QList<QString> &IncidentList = Tmp0);
    ~Event();
    QList<QString> GetIncidents()
    {
        return *Incidents;
    }

    //显示当前行的步骤信息
    void ItemShow();

   private slots:

    //添加步骤
    void on_pushButton_clicked();

    //删除步骤——该步骤已完成
    void on_pushButton_2_clicked();

    //双击该步骤进行修改
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
private:
    Ui::Event *ui;
    QString CurrentIncident;
    QList<QString> *Incidents;
};

#endif // EVENT_H
