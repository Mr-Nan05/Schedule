#ifndef REMIND_H
#define REMIND_H

#include <QTime>
#include <QDialog>

namespace Ui {
class Remind;
}

class Remind : public QDialog
{
    Q_OBJECT

public:
    explicit Remind(QWidget *parent = nullptr);
    ~Remind();

    QTime GetRemindTime()
    {
        return aRemindTime;
    }

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Remind *ui;

    QTime aRemindTime;
    QString aReminder;
};

#endif // REMIND_H
