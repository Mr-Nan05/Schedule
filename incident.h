#ifndef INCIDENT_H
#define INCIDENT_H

#include <QDialog>

namespace Ui {
class Incident;
}

class Incident : public QDialog
{
    Q_OBJECT

public:
    explicit Incident(QWidget *parent = nullptr);
    Incident(QWidget *parent = nullptr, QString str = "");
    ~Incident();
    QString GetIncident()
    {
        return incident;
    }

private slots:
 //获取输入步骤信息
 void on_buttonBox_accepted();


private:
    Ui::Incident *ui;
    QString incident;
};

#endif // INCIDENT_H
