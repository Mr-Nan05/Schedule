#include "event.h"


Event::Event(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Event)
{
    ui->setupUi(this);
    ItemShow();
}

Event::Event(QWidget *parent,QList<QString> &IncidentList):
    QDialog(parent),
    ui(new Ui::Event)
{
    ui->setupUi(this);
    Incidents = &IncidentList;
    ItemShow();
}

Event::~Event()
{
    delete ui;
}

void Event::ItemShow()
{
    ui->listWidget->clear();
    foreach(const QString &aIncident,(*Incidents)){
        QListWidgetItem *aItem = new QListWidgetItem;
        aItem->setText(aIncident);
        ui->listWidget->addItem(aItem);
    }
}

void Event::on_pushButton_clicked()
{
    Incident *aIncident = new Incident(this,"");
    aIncident->exec();
    if(aIncident->result() == aIncident->Rejected)
        return;
    else (*Incidents).push_back(aIncident->GetIncident());
    ItemShow();
}

void Event::on_pushButton_2_clicked()
{
    QListWidgetItem *aItem = nullptr;
    aItem = ui->listWidget->currentItem();

    if(aItem != nullptr){
        QString IncidentName = aItem->text();
        (*Incidents).removeOne(IncidentName);
    }
    ItemShow();
}

void Event::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    CurrentIncident = item->text();
    Incident *aIncident = new Incident(this,CurrentIncident);
    aIncident->exec();
    if(aIncident->result() == aIncident->Rejected)
        return;
    else (*Incidents).removeOne(CurrentIncident);
    (*Incidents).push_back(aIncident->GetIncident());
    ItemShow();
}

