#ifndef LIST_H
#define LIST_H
#include <QMultiMap>
#include <QDialog>
#include <QList>
#include <QMap>
namespace Ui {
class List;
}

class List : public QDialog
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = nullptr);
    ~List();

    QString GetEventlist()
    {
        return Event;
    }

private slots:

 //获得输入的事件标题
 void on_buttonBox_accepted();


private:
    Ui::List *ui;
    QString Event;
};

#endif // LIST_H
