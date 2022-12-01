#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include "confirm.h"

namespace Ui {
class Interface;
}

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
    void Run(int state);


private slots:
    void on_pushButton_equal_clicked();

    void on_pushButton_inequal_clicked();

    void on_pushButton_uncertain_clicked();

private:
    Ui::Interface *ui;
    Confirm c;
    Pair p; //当前测试的程序对
    int index; //当前测试的程序对在EqualPairs里对应的下标
};

#endif // INTERFACE_H
