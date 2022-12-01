#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    c.ReadEqualData();
    this->Run(0);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::Run(int state)
{
    if(c.Finish())
    {
        this->hide();
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(this, "提示", "人工等价判断结束，判断结果在result文件夹中。");
    }
    else{
        if(state == 0)
        {
            index = c.ConfirmPair("", "");
        }
        else
        {
            index = c.ConfirmPair(p.file1, p.file2);
        }
        p = c.getPair(index);
        ui->label_1->setText(p.file1);
        QFile file1(p.file1);
        if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<p.file1<<"文件未打开！";
        }
        QString data1;
        while(!file1.atEnd())
        {
            QByteArray array = file1.readLine();
            QString str(array);
            data1.append(str);
        }
        ui->textBrowser_1->setText(data1);

        ui->label_2->setText(p.file2);
        QFile file2(p.file2);
        if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<p.file2<<"文件未打开！";
        }
        QString data2;
        while(!file2.atEnd())
        {
            QByteArray array = file2.readLine();
            QString str(array);
            data2.append(str);
        }
        ui->textBrowser_2->setText(data2);
        file1.close();
        file2.close();
    }
}


void Interface::on_pushButton_equal_clicked()
{
    Run(0);
}


void Interface::on_pushButton_inequal_clicked()
{
    c.ChangeState(index, p, 1);
    Run(1);
}


void Interface::on_pushButton_uncertain_clicked()
{
    c.ChangeState(index, p, 2);
    Run(2);
}

