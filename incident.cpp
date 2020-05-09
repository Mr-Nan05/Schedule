#include "incident.h"
#include "ui_incident.h"

Incident::Incident(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Incident)
{
    ui->setupUi(this);
}

Incident::Incident(QWidget *parent, QString str):
    QDialog(parent),
    ui(new Ui::Incident)
{
    ui->setupUi(this);
    ui->textEdit->setText(str);
}

Incident::~Incident()
{
    delete ui;
}

void Incident::on_buttonBox_accepted()
{
    incident = ui->textEdit->toPlainText();
}

